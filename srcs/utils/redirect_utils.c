/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpedrosa <rpedrosa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 12:34:23 by rpedrosa          #+#    #+#             */
/*   Updated: 2025/04/17 15:58:51 by rpedrosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"
#include "../../incs/parsing.h"
/* 
	@brief: checks errors of multiple redirect chars following each other then calls the util to copy the files to their matrixes
	@arguments: command is the main struct with all the data
                arg is the current arg we found the redirect
				talbe is the current table we working on
				chr is the index of the redirect sign in the string (arg)
    @return: 0 in case of success.
             1 or any other number in case of error. */

int	assign_file(t_data *command, int table, int arg, int chr)
{
	char *current;
	int error;

	current = command->table[table]->args[arg];
	if (current[chr + 1] == '<' || current[chr + 1] == '>')
		return (print_error(SYNTAX_ERROR, &command->exit_code), 1);
	if (current[chr + 1] == '\0')
	{
		if (command->table[table]->args[arg + 1][0] == '<' || \
		command->table[table]->args[arg + 1][0] == '>')
			return (print_error(SYNTAX_ERROR, &command->exit_code), 1);
	}
	if (current[chr] == '<')
		error = assign_util_infile(command, arg, table, chr);
	if (current[chr] == '>')
		error = assign_util_outfile(command, arg, table, chr);
	return (error);
}

char *copy_red(char *str)
{
	int	len;
	int tmp;
	char *dup;
	int	i;

	if (!str)
		return(NULL);
	i = 0;
	len = ft_strlen(str);
	tmp = len;
	while (tmp > 0 && str[tmp] != '>' && str[tmp] != '<')
		tmp--;
	dup = malloc (len - tmp + 1);
	if (!dup)
		return (NULL);
	if (str[tmp] == '<' || str[tmp] == '>')
    	tmp++;
	while (tmp < len)
		dup[i++] = str[tmp++];
	dup[i] = '\0';
	return (dup);
}
