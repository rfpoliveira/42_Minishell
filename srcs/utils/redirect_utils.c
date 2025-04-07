/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpedrosa <rpedrosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 12:34:23 by rpedrosa          #+#    #+#             */
/*   Updated: 2025/04/07 15:07:08 by rpedrosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int	assign_double_out(t_command *command, char *current, int arg, int table)
{
	if (current[arg + 2] == '<' || current[arg + 2] == '>')
		return (print_error(SYNTAX_ERROR, command->exit_code), 1);
	if (current[arg + 2] == '\0')
	{
		if (command->table[table + 1][0] == '<' || \
		command->table[table + 1][0] == '>')
			return (print_error(SYNTAX_ERROR, command->exit_code), 1);
	}
	if (assign_file(command->table[table]->double_out, command, arg, table) != 0)
		return (1);
	if (reorganize_args(command, table, arg) != 0)
		return (1);
	return (0);
}

int	assign_double_in(t_command *command, char *current, int arg, int table)
{
	if (current[arg + 2] == '<' || current[arg + 2] == '>')
		return (print_error(SYNTAX_ERROR, command->exit_code), 1);
	if (current[arg + 2] == '\0')
	{
		if (command->table[table + 1][0] == '<' || \
		command->table[table + 1][0] == '>')
			return (print_error(SYNTAX_ERROR, command->exit_code), 1);
	}
	if (assign_file(command->table[table]->double_in, command, arg, table) != 0)
		return (1);
	if (reorganize_args(command, table, arg) != 0)
		return (1);
	return (0);
}
int	assign_outfile(t_command *command, char *current, int arg, int table)
{
	if (current[arg + 1] == '<')
		return (print_error(SYNTAX_ERROR, command->exit_code), 1);
	if (current[arg + 1] == '\0')
	{
		if (command->table[table + 1][0] == '<' || \
		command->table[table + 1][0] == '>')
			return (print_error(SYNTAX_ERROR, command->exit_code), 1);
	}
	if (assign_file(command->table[table]->outfile, command, arg, table) != 0)
		return (1);
	if (reorganize_args(command, table, arg) != 0)
		return (1);
	return (0);
}

int	assign_infile(t_command *command, char *current, int arg, int table)
{
	if (current[arg + 1] == '>')
		return (print_error(SYNTAX_ERROR, command->exit_code), 1);
	if (current[arg + 1] == '\0')
	{
		if (command->table[table + 1][0] == '<' || \
		command->table[table + 1][0] == '>')
			return (print_error(SYNTAX_ERROR, command->exit_code), 1);
	}
	if (assign_file(command->table[table]->infile, command, arg, table) != 0)
		return (1);
	if (reorganize_args(command, table, arg) != 0)
		return (1);
	return (0);
}
