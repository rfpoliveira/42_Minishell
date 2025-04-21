/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_file_assign.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpedrosa <rpedrosa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 15:07:30 by rpedrosa          #+#    #+#             */
/*   Updated: 2025/04/21 11:48:57 by rpedrosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"
#include "../../incs/parsing.h"
/* EVERY FUNCTION IN THE FILE WORKS THIS WAY
	@brief: takes the info from the arguments and saves it in the matrix that refer to the files
	@arguments: command is the main struct with all the data
                arg is the current arg we found the redirect
				talbe is the current table we working on
				chr is the index of the redirect sign in the string (arg)
	@notes: I split the args and depending on the result i can tell what case I got and select what is the file: 
			exemples: echo test > file, echo test> file, echo test >file, echo test>file.
					in the first 2 cases we now next to the sign is a null char, so the next arg is the file.
					in the third and fourth case the redirect is in the same arg as the file so we split them and the files are what comes next,
					we have a loop in the case of multiple redirections with no whitespaces.
    @return: 0 in case of success.
             1 or any other number in case of error.
*/
int	assign_util_infile(t_data *command, int arg, int table, int chr)
{
	int i;
	char **tmp;
	char **file;

	if (chr > 0 && command->table[table]->args[arg][chr - 1] == '<')
		file = command->table[table]->double_in;
	else
		file = command->table[table]->infile;
	i = 0;
	while (file[i])
		i++;
	if (command->table[table]->args[arg][chr + 1] == '\0')
		file[i++] = copy_red(command->table[table]->args[arg + 1]);
	else
	{
		if (chr != 0 || (file == command->table[table]->double_in && chr != 1))
			command->table[table]->in_iter++;
		tmp = parsing_split(command->table[table]->args[arg], '<');
		file[i++] = copy_red(tmp[command->table[table]->in_iter]);
		matrix_free(tmp);
	}
	file[i] = NULL;
	return  (0);
}

int	assign_util_outfile(t_data *command, int arg, int table, int chr)
{
	int i;
	char **tmp;
	char **file;

	tmp = NULL;
	if (chr > 0 && command->table[table]->args[arg][chr - 1] == '>')
		file = command->table[table]->double_out;
	else
		file = command->table[table]->outfile;
	i = 0;
	while (file[i])
		i++;
	if (command->table[table]->args[arg][chr + 1] == '\0')
		file[i++] = copy_red(command->table[table]->args[arg + 1]);
	else
	{
		if (chr != 0 || (file == command->table[table]->double_out && chr != 1))
			command->table[table]->out_iter++;
		tmp = parsing_split(command->table[table]->args[arg], '>');
		file[i++] = copy_red(tmp[command->table[table]->out_iter]);
		matrix_free(tmp);
	}
	file[i] = NULL;
	return (0);
}
