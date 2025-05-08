/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpedrosa <rpedrosa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 15:25:40 by rpedrosa          #+#    #+#             */
/*   Updated: 2025/05/08 15:59:58 by rpedrosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"
#include "../../incs/parsing.h"

/** 
 @brief ignores the quote and copies until the next one;
 @param s is the string from which we will take out some chars
 @param tmp is the new string that was pass on the data to
 @param i the index of the quote found
 @param len the index where we put the new info in the tmp
*/
static void	delete_quotes_util(char **s, char **temp, int *i, int *len)
{
	int	quote;

	quote = (*s)[*i];
	(*i)++;
	while ((*s)[*i] && (*s)[*i] != quote)
	{
		(*temp)[(*len)] = (*s)[(*i)];
		(*len)++;
		(*i)++;
	}
}
/** 
 @brief deletes quotes from s 
 @param s is the string from which we will take out some chars
 @return: 0 in case of success, 
		  1 or any other number in case of errors. 
*/
static int	delete_quotes(char **s, t_data *command)
{
	int		i;
	int		len;
	char	*temp;

	i = 0;
	len = after_quotes_strlen(s);
	temp = ft_calloc(len + 1, sizeof(char));
	if (!temp)
		return (print_error(MALLOC_ERROR, &command->exit_code), 1);
	temp[len] = '\0';
	len = 0;
	while ((*s)[i])
	{
		if ((*s)[i] == 34 || (*s)[i] == 39)
			delete_quotes_util(s, &temp, &i, &len);
		else
			temp[len++] = (*s)[i];
		if (!(*s)[i])
			break ;
		i++;
	}
	free((*s));
	*s = temp;
	return (0);
}
/**
 @brief deletes quotes and redirect signs from the files saved
 @param file is the current file to check
 @param command is the main struct with all the data
 @return 0 in case of success,
		 1 or any other number in case of errors. 
*/
static int	check_for_quotes(char **file, t_data *command)
{
	int	i;
	int	j;
	int	error;

	i = -1;
	j = -1;
	error = 0;
	while (file[++i])
	{
		while (file[i][++j])
		{
			if (file[i][j] == 34 || file[i][j] == 39)
			{
				error = delete_quotes(&file[i], command);
				break ;
			}
		}
		j = -1;
	}
	return (error);
}
/**
 @brief iterates and calls and the functions need to delete quotes 
			and redirects from everything saved.
 @param command is the main struct with all the data
 @return 0 in case of success,
		 1 or any other number in case of errors. 
*/
int	handle_quotes(t_data *command)
{
	int	error;
	int	i;

	i = -1;
	error = 0;
	while (command->table[++i])
	{
		error = check_for_quotes(command->table[i]->args, command);
		if (command->table[i]->infile)
			error = check_for_quotes(command->table[i]->infile, command);
		if (command->table[i]->outfile)
			error = check_for_quotes(command->table[i]->outfile, command);
		if (command->table[i]->double_out)
			error = check_for_quotes(command->table[i]->double_out, command);
		if (command->table[i]->double_in)
			error = check_for_quotes(command->table[i]->double_in, command);
	}
	return (error);
}
