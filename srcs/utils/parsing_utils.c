/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpedrosa <rpedrosa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 15:25:40 by rpedrosa          #+#    #+#             */
/*   Updated: 2025/04/21 19:29:10 by rpedrosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"
#include "../../incs/parsing.h"

/* @brief: deletes A and B from s 
	@arguments: s is the string from which we will take out some chars
				A and B and the chars to take out
	used to take out quotes, double quotes and redirect symbols
	@return: 0 in case of success
			 1 or any other number in case of errors. 
*/

int	delete_sigs(char **s, char A, char B, int *exit_code)
{
	int		i;
	char	*temp;
	int		len;

	i = 0;
	if (*s == NULL)
		return (0);
	len = after_sig_strlen(*s, A, B);
	temp = malloc(len + 1);
	if (temp == NULL)
		return (print_error(MALLOC_ERROR, exit_code), 1);
	temp[len] = '\0';
	len = 0;
	while ((*s)[i])
	{
		if ((*s)[i] != A && (*s)[i] != B)
		{
			temp[len] = (*s)[i];
			len++;
		}
		i++;
	}
	ft_strlcpy(*s, temp, len + 1);
	free(temp);
	return (0);
}
/* @brief: deletes quotes from s 
	@arguments: s is the string from which we will take out some chars
	@return: 0 in case of success
			 1 or any other number in case of errors. 
*/

static int	delete_quotes(char **s, int *exit_code)
{
	int		i;
	int		len;
	char	*temp;

	i = -1;
	len = after_quotes_strlen(*s);
	temp = malloc(len + 1);
	if (!temp)
		return (print_error(MALLOC_ERROR, exit_code), 1);
	temp[len] = '\0';
	len = 0;
	while((*s)[++i])
	{
		if ((*s)[i] == 34)
		{
			i++;
			while((*s)[i] != 34 && (*s)[i])
				temp[len++] = (*s)[i++];
		}
		else if ((*s)[i] == 39)
		{
			i++;
			while((*s)[i] != 39 && (*s)[i])
				temp[len++] = (*s)[i++];
		}
		else
			temp[len++] = (*s)[i];
	}
	free((*s));
	*s = ft_strdup(temp);
		if (*s == NULL)
			return (free(temp), print_error(MALLOC_ERROR, exit_code), 1);
	return (free(temp), 0);
}
/* @brief: deletes quotes and redirect signs from the files saved
	@arguments: file is the current file to check
				command is the main struct with all the data
	@return: 0 in case of success
			 1 or any other number in case of errors. 
*/

int	delete_sigs_from_outinfiles(char **file, t_data *command)
{
	int	i;
	int	error;

	i = -1;
	error = 0;
	while(file[++i])
	{
		error = delete_sigs(&file[i], '<', '>', &command->exit_code);
		error = delete_quotes(&file[i], &command->exit_code);
	}
	return (error);
}
/* @brief: iterates and calls and the functions need to delete quotes and redirects from everything saved.
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
	j = 0;
	error = 0;
	while (command->table[++i])
	{
		while (command->table[i]->args[j])
		{
			error = delete_quotes(&command->table[i]->args[j], &command->exit_code);
			j++;
		}
		if (command->table[i]->infile)
			error = delete_sigs_from_outinfiles(command->table[i]->infile, command);
		if (command->table[i]->outfile)
			error = delete_sigs_from_outinfiles(command->table[i]->outfile, command);
		if (command->table[i]->double_out)
			error = delete_sigs_from_outinfiles(command->table[i]->double_out, command);
		if (command->table[i]->double_in)
			error = delete_sigs_from_outinfiles(command->table[i]->double_in, command);
		j = 0;
	}
	return (error);
}
/* @brief: checks if there is a even number of quotes.
	@arguments: s is the current string (arg or file) being checked
				exit_code saves the exit code of the last command
	if we have and unclosed quote we give an error
	if that quote is bettewn other quotes it should be ignored
	@return: 0 in case of success
			 1 or any other number in case of errors. 
*/

int	quote_counter(char **s, int *exit_code)
{
	int	i;
	int	j;
	int	count;
	int	flag;
	
	i = -1;
	j = -1;
	count = 0;
	if (!s)
		return (0);
	while (s[++j])
	{
		while (s[j][++i])
		{
			if (s[j][i] == 34 || s[j][i] == 39)
			{
				flag = s[j][i];
				count++;
				if(s[j][i + 1] != '\0') 
					i += skip_quotes(s[j], i);
				if (s[j][i - 1] == flag)
					count++;
			}
		}
	}
	if (count % 2 == 0)
		return (0);
	else
		return (print_error(QUOTE_ERROR, exit_code), 1);
}
