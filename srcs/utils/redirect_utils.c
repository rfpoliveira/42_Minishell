/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpedrosa <rpedrosa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 12:34:23 by rpedrosa          #+#    #+#             */
/*   Updated: 2025/07/07 16:17:13 by rpedrosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"
#include "../../incs/parsing.h"
/**
 @brief: checks errors of multiple redirect chars following each other 
		 then calls the util to copy the files to their matrixes
 @param command is the main struct with all the data
 @param arg is the current arg we found the redirect
 @param table is the current table we working on
 @param chr is the index of the redirect sign in the string (arg)
 @note we cant have empty netx to redirect of multiple diferent signs 
	   (<<> or >< for exemple)
 @return 0 in case of success.
             1 or any other number in case of error.
*/
int	assign_file(t_data *command, int table, int arg, int chr)
{
	char	*current;
	int		error;

	current = command->table[table]->args[arg];
	if (current[chr] == '<' && current[chr + 1] == '>')
	{
		if (chr == 0 || (chr > 0 && current[chr - 1] != '<'))
			return (assign_util_infile(command, arg, table, chr));
	}
	else if (current[chr + 1] == '<' || current[chr + 1] == '>')
		return (print_error(SYNTAX_ERROR, &command->exit_code), 1);
	if (current[chr + 1] == '\0')
	{
		if (command->table[table]->args[arg + 1] == NULL)
			return (print_error(SYNTAX_ERROR, &command->exit_code), 1);
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

/**
 @brief alloc and copies a string until it finds redirect symbols or '\0' 
 @param str is the string to be copied
 @note based of strdup
 @return the copy until the correct point
*/
char	*copy_red(char *str)
{
	int		len;
	char	*dup;
	int		i;

	if (!str)
		return (NULL);
	i = -1;
	len = 0;
	while (str[len] && str[len] != '>' && str[len] != '<')
		len++;
	dup = malloc (len + 1);
	if (!dup)
		return (NULL);
	while (str[++i] && str[i] != '>' && str[i] != '<')
		dup[i] = str[i];
	dup[i] = '\0';
	return (dup);
}
