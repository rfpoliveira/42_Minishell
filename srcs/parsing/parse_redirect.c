/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpedrosa <rpedrosa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 16:34:59 by rpedrosa          #+#    #+#             */
/*   Updated: 2025/04/10 15:01:55 by rpedrosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"
#include "../../incs/parsing.h"

int	check_red_out(t_data *command, int chr, int table, int arg)
{
	char *current;

	current = command->table[table]->args[arg];
	if (current[chr + 1] == '>')
		return (assign_double_out(command, table, arg, chr));
	else
		return (assign_outfile(command, table, arg, chr));
}

int	check_red_in(t_data *command, int chr, int table, int arg)
{
	char *current;

	current = command->table[table]->args[arg];
	if (current[chr + 1] == '<')
		return (assign_double_in(command, table, arg, chr));
	else
		return (assign_infile(command, table, arg, chr));
}

int check_for_red(t_data *command, int table, int arg)
{
	int chr;
	char *current;

	chr = -1;
	current = command->table[table]->args[arg];
	while(current[++chr])
	{
		if (current[chr] == '<')
			return (check_red_in(command, chr, table, arg));
		else if (current[chr] == '>')
			return (check_red_out(command, chr, table, arg));
	}
	return (0);
}

static int reorganize_afer_redirect(t_data *command, int curr_table)
{
 	char **tmp;
	int	new_arg_count;
	t_simple_command *current;

	current = command->table[curr_table];
	new_arg_count = new_arg_counter(current, current->args);
	current->number_args = new_arg_count;
 	tmp = malloc(sizeof(char *) * new_arg_count + 8);
	if (tmp == NULL)
		return (print_error(MALLOC_ERROR, &command->exit_code), 1);
	tmp[new_arg_count] = NULL;
	if (populate_tmp(tmp, command, current) != 0)
		return (matrix_free(tmp), 1);
	matrix_free(current->args);
	current->args = tmp;
	return (0);
}

int	handle_redirect(t_data *command)
{
	int i;
	int j;

	i = -1;
	j = -1;
	while (command->table[++i])
	{
		while (command->table[i]->args[++j])
		{
			if (check_for_red(command, i, j) != 0)
				return (1);
		}
		j = -1;
	}
	while (command->table[++j])
	{
		if (reorganize_afer_redirect(command, j) != 0)
			return (1);
	}
	return (0);
}
