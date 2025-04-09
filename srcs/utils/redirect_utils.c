/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpedrosa <rpedrosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 12:34:23 by rpedrosa          #+#    #+#             */
/*   Updated: 2025/04/09 16:09:48 by rpedrosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"
#include "../../incs/parsing.h"

int	assign_double_out(t_data *command, int table, int arg, int chr)
{
	char *current;

	current = command->table[table]->args[arg];
	if (current[chr + 2] == '<' || current[chr + 2] == '>')
		return (print_error(SYNTAX_ERROR, &command->exit_code), 1);
	if (current[chr + 2] == '\0')
	{
		if (command->table[table + 1]->args[arg][0] == '<' || \
		command->table[table + 1]->args[arg][0] == '>')
			return (print_error(SYNTAX_ERROR, &command->exit_code), 1);
	}
	if (assign_util_double_out(command, arg, table, chr) != 0)
		return (1);
/* 	if (reorganize_args(command, table, arg) != 0)
		return (1); */
	return (0);
}

int	assign_double_in(t_data *command, int table, int arg, int chr)
{
	char *current;

	current = command->table[table]->args[arg];
	if (current[chr + 2] == '<' || current[chr + 2] == '>')
		return (print_error(SYNTAX_ERROR, &command->exit_code), 1);
	if (current[chr + 2] == '\0')
	{
		if (command->table[table + 1]->args[arg][0] == '<' || \
		command->table[table + 1]->args[arg][0] == '>')
			return (print_error(SYNTAX_ERROR, &command->exit_code), 1);
	}
	if (assign_util_double_in(command, arg, table, chr) != 0)
		return (1);
/* 	if (reorganize_args(command, table, arg) != 0)
		return (1); */
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
		if (command->table[table + 1]->args[arg][0] == '<' || \
		command->table[table + 1]->args[arg][0] == '>')
			return (print_error(SYNTAX_ERROR, &command->exit_code), 1);
	}
	if (assign_util_outfile(command, arg, table, chr) != 0)
		return (1);
/* 	if (reorganize_args(command, table, arg) != 0)
		return (1); */
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
		if (command->table[table + 1]->args[arg][0] == '<' || \
		command->table[table + 1]->args[arg][0] == '>')
			return (print_error(SYNTAX_ERROR, &command->exit_code), 1);
	}
	if (assign_util_infile(command, arg, table, chr) != 0)
		return (1);
/* 	if (reorganize_args(command, table, arg) != 0)
		return (1); */
	return (0);
}
