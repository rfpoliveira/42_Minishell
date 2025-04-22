/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_file_assign.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpedrosa <rpedrosa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 15:07:30 by rpedrosa          #+#    #+#             */
/*   Updated: 2025/04/22 11:26:15 by rpedrosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"
#include "../../incs/parsing.h"

/* EVERY FUNCTION IN THE FILE WORKS THIS WAY
	@brief: takes the info from the arguments and saves it in the matrix
	@arguments: command is the main struct with all the data
                arg is the current arg we found the redirect
				talbe is the current table we working on
				chr is the index of the redirect sign in the string (arg)
	@notes: I iterate until null 
			(the index where the new redirect will be assigned)
			then check if the index after the redirect signal is null 
			(echo> test or echo > test)
			that case we simply copy until the next symbol if there is any
			in the other cases we split the argument 
			and use the iter variables to store if any previous infiles have 
			already been saved and that makes sure we save the next one.
			we always null terminate so when the next call of this function
			enter counts the file infex correctly
    @return: 0 in case of success.
             1 or any other number in case of error.
*/

int	assign_util_infile(t_data *command, int arg, int table, int chr)
{
	int		i;
	char	**tmp;
	char	**file;

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
		if ((file == command->table[table]->infile && chr != 0) || \
		(file == command->table[table]->double_in && chr != 1))
			command->table[table]->in_iter++;
		tmp = parsing_split(command->table[table]->args[arg], '<');
		file[i++] = copy_red(tmp[command->table[table]->in_iter]);
		matrix_free(tmp);
	}
	file[i] = NULL;
	return (0);
}

int	assign_util_outfile(t_data *command, int arg, int table, int chr)
{
	int		i;
	char	**tmp;
	char	**file;

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
		if ((file == command->table[table]->outfile && chr != 0) || \
		(file == command->table[table]->double_out && chr != 1))
			command->table[table]->out_iter++;
		tmp = parsing_split(command->table[table]->args[arg], '>');
		file[i++] = copy_red(tmp[command->table[table]->out_iter]);
		matrix_free(tmp);
	}
	file[i] = NULL;
	return (0);
}
