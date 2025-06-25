/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_empty_args.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpedrosa <rpedrosa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 10:11:46 by rpedrosa          #+#    #+#             */
/*   Updated: 2025/06/25 11:04:57 by rpedrosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"
#include "../../incs/parsing.h"

static int	arg_counter(t_simple_command *current)
{
	int j;
	int count;

	j = 0;
	count = 0;
	while(current->args[j])
	{
		if (ft_strncmp("", current->args[j], 1) != 0)
			count++;
		j++;
	}
	return (count);
}

static int	pop_tmp(char **tmp, t_data *command, int curr_table)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while(command->table[curr_table]->args[i])
	{
		if (ft_strncmp(command->table[curr_table]->args[i], "", 1) != 0)
		{
			tmp[j] = ft_strdup(command->table[curr_table]->args[i]);
			if (tmp[j] == NULL)
				return (matrix_free(tmp), 1);
			j++;
		}
		i++;
	}
	return (0);
}
static int	free_n_dup(char **tmp, t_data *command, int curr_table)
{
	int i;

	i = 0;
	matrix_free(command->table[curr_table]->args);
	command->table[curr_table]->args = malloc(sizeof(char *) \
	* command->table[curr_table]->number_args + 8);
	if (command->table[curr_table]->args == NULL)
		return (matrix_free(tmp), 1);
	while (tmp[i])
	{
		command->table[curr_table]->args[i] = ft_strdup(tmp[i]);
		if (command->table[curr_table]->args[i] == NULL)
		{
			matrix_free(command->table[curr_table]->args);
			return (matrix_free(tmp), 1);
		}
		i++;
	}
	command->table[curr_table]->args[i] = NULL;
	return (matrix_free(tmp), 0);
}

int	handle_empty_args (t_data *command)
{
	int		curr_table;
	int		new_arg_count;
	char	**tmp;
	
	if (command->number_simple_commands == 0)
		return (0);
	curr_table = 0;
	while (command->table[curr_table])
	{
		new_arg_count = arg_counter(command->table[curr_table]);
		command->table[curr_table]->number_args = new_arg_count;
		tmp = malloc(sizeof(char *) * new_arg_count + 8);
		if (tmp == NULL)
			return (print_error(MALLOC_ERROR, &command->exit_code), 1);
		tmp[new_arg_count] = NULL;
		if (pop_tmp(tmp, command, curr_table) != 0)
			return (matrix_free(tmp), 1);
		if (free_n_dup(tmp, command, curr_table) != 0)
			return (print_error(MALLOC_ERROR, &command->exit_code), 1);
		curr_table++;
	}
	return (0);
}