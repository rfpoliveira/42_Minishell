/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpedrosa <rpedrosa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 12:34:23 by rpedrosa          #+#    #+#             */
/*   Updated: 2025/04/11 15:31:55 by rpedrosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"
#include "../../incs/parsing.h"

/* void	re_check_red(t_data *command, char **file, int table, int arg)
{
	int	i;
	int j;
	
	i = -1;
	j = 0;
	while (file[++i])
	{
		while (file[i][++j])
		{
			if (file[i][j] == '<')
		}
	}
} */

int	assign_double_out(t_data *command, int table, int arg, int chr)
{
	char *current;

	current = command->table[table]->args[arg];
	if (current[chr + 2] == '<' || current[chr + 2] == '>')
		return (print_error(SYNTAX_ERROR, &command->exit_code), 1);
	if (current[chr + 2] == '\0')
	{
		if (command->table[table]->args[arg + 1][0] == '<' || \
		command->table[table]->args[arg + 1][0] == '>')
			return (print_error(SYNTAX_ERROR, &command->exit_code), 1);
	}
	if (assign_util_double_out(command, arg, table, chr) != 0)
		return (1);
/* 	re_check_red(command, command->table[table]->double_in, table, arg);
 */	return (0);
}

int	assign_double_in(t_data *command, int table, int arg, int chr)
{
	char *current;

	current = command->table[table]->args[arg];
	if (current[chr + 2] == '<' || current[chr + 2] == '>')
		return (print_error(SYNTAX_ERROR, &command->exit_code), 1);
	if (current[chr + 2] == '\0')
	{
		if (command->table[table]->args[arg + 1][0] == '<' || \
		command->table[table]->args[arg + 1][0] == '>')
			return (print_error(SYNTAX_ERROR, &command->exit_code), 1);
	}
	if (assign_util_double_in(command, arg, table, chr) != 0)
		return (1);
	return (0);
}
int	assign_outfile(t_data *command, int table, int arg, int chr)
{
	char *current;

	current = command->table[table]->args[arg];
	if (current[chr + 1] == '<')
		return (print_error(SYNTAX_ERROR, &command->exit_code), 1);
	if (current[chr + 1] == '\0')
	{
		if (command->table[table]->args[arg + 1][0] == '<' || \
		command->table[table]->args[arg + 1][0] == '>')
			return (print_error(SYNTAX_ERROR, &command->exit_code), 1);
	}
	if (assign_util_outfile(command, arg, table, chr) != 0)
		return (1);
	return (0);
}

int	assign_infile(t_data *command, int table, int arg, int chr)
{
	char *current;

	current = command->table[table]->args[arg];
	if (current[chr + 1] == '>')
		return (print_error(SYNTAX_ERROR, &command->exit_code), 1);
	if (current[chr + 1] == '\0')
	{
		if (command->table[table]->args[arg + 1][0] == '<' || \
		command->table[table]->args[arg + 1][0] == '>')
			return (print_error(SYNTAX_ERROR, &command->exit_code), 1);
	}
	if (assign_util_infile(command, arg, table, chr) != 0)
		return (1);
	return (0);
}
