/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpedrosa <rpedrosa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 16:34:59 by rpedrosa          #+#    #+#             */
/*   Updated: 2025/04/16 14:13:20 by rpedrosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"
#include "../../incs/parsing.h"
/* @brief: separates bettewn ">" and ">>"
	@arguments: command is the main struct with all the info
				curr_table is the index in the matrix of the current table we working on.
				arg is the current arg we working on.
				chr the index of the ">" that was found.
	@return: 0 in case of sucess
			 any other number in case of errors */
int	check_red_out(t_data *command, int chr, int table, int arg)
{
	char *current;

	current = command->table[table]->args[arg];
	if (current[chr + 1] == '>')
		return (assign_double_out(command, table, arg, chr));
	else
		return (assign_outfile(command, table, arg, chr));
}
/* @brief: separates bettewn "<" and "<<"
	@arguments: command is the main struct with all the info
				curr_table is the index in the matrix of the current table we working on.
				arg is the current arg we working on.
				chr the index of the "<" that was found.
	@return: 0 in case of sucess
			 any other number in case of errors */
int	check_red_in(t_data *command, int chr, int table, int arg)
{
	char *current;

	current = command->table[table]->args[arg];
	if (current[chr + 1] == '<')
		return (assign_double_in(command, table, arg, chr));
	else
		return (assign_infile(command, table, arg, chr));
}
/* @brief: iterates the current arg to check if there are redirects
	splits bettewn ins and outs
	@arguments: command is the main struct with all the info
				curr_table is the index in the matrix of the current table we working on.
				arg is the current arg we working on.
	@return: 0 in case of sucess
			 any other number in case of errors */
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
/* @brief: takes out of the args what are redirects
	@arguments: command is the main struct with all the info
				curr_table is the index in the matrix of the current table we working on.
	counts the number of the args that we are keeping(new_arg_count).
	allocates memory for the new matrix,
	then copies only the args that we are maintaning to the new matrix (populate_tmp).
	@return: 0 in case of sucess
			 MALLOC_ERROR or any number in case of errors */
static int reorganize_after_redirect(t_data *command, int curr_table)
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
/* @brief: iterates all the args locking for redirect signs, 
	then reoganize the arguments (takes out of the args what are redirects)
	@return: 0 in case of sucess
			 1 in case of errors */
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
		if (reorganize_after_redirect(command, j) != 0)
			return (1);
	}
	return (0);
}
