/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpedrosa <rpedrosa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 15:25:40 by rpedrosa          #+#    #+#             */
/*   Updated: 2025/04/22 11:12:15 by rpedrosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"
#include "../../incs/parsing.h"

/* @brief: deletes quotes from s 
	@arguments: s is the string from which we will take out some chars
	@util: ignores the quote and copies until the next one;
	@return: 0 in case of success
			 1 or any other number in case of errors. 
*/

static void	delete_quotes_util(char **s, char **temp, int *i, int *len)
{
	int	quote;

	quote = (*s)[*i];
	(*i)++;
	while ((*s)[*i] != quote && (*s)[*i])
		(*temp)[(*len)++] = (*s)[(*i)++];
}

static int	delete_quotes(char **s, t_data *command)
{
	int		i;
	int		len;
	char	*temp;

	i = -1;
	len = after_quotes_strlen(*s);
	temp = malloc(len + 1);
	if (!temp)
		return (print_error(MALLOC_ERROR, &command->exit_code), 1);
	temp[len] = '\0';
	len = 0;
	while ((*s)[++i])
	{
		if ((*s)[i] == 34 || (*s)[i] == 39)
			delete_quotes_util(s, &temp, &i, &len);
		else
			temp[len++] = (*s)[i];
	}
	free((*s));
	*s = ft_strdup(temp);
	if (*s == NULL)
		return (free(temp), print_error(MALLOC_ERROR, &command->exit_code), 1);
	return (free(temp), 0);
}
/* @brief: deletes quotes and redirect signs from the files saved
	@arguments: file is the current file to check
				command is the main struct with all the data
	@return: 0 in case of success
			 1 or any other number in case of errors. 
*/

static int	delete_quotes_files(char **file, t_data *command)
{
	int	i;
	int	error;

	i = -1;
	error = 0;
	while (file[++i])
	{
		/* error = delete_sigs(&file[i], '<', '>', &command->exit_code); */
		error = delete_quotes(&file[i], &command->exit_code);
	}
	return (error);
}
/* @brief: iterates and calls and the functions need to delete quotes 
			and redirects from everything saved.
	@arguments: command is the main struct with all the data
	@return: 0 in case of success
			 1 or any other number in case of errors. 
*/

int	handle_quotes(t_data *command)
{
	int	error;
	int	i;
	int	j;

	i = -1;
	j = -1;
	error = 0;
	while (command->table[++i])
	{
		while (command->table[i]->args[++j])
			error = delete_quotes(&command->table[i]->args[j], command);
		if (command->table[i]->infile)
			error = delete_quotes_files(command->table[i]->infile, command);
		if (command->table[i]->outfile)
			error = delete_quotes_files(command->table[i]->outfile, command);
		if (command->table[i]->double_out)
			error = delete_quotes_files(command->table[i]->double_out, command);
		if (command->table[i]->double_in)
			error = delete_quotes_files(command->table[i]->double_in, command);
		j = -1;
	}
	return (error);
}
