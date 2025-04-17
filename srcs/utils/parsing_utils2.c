/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpedrosa <rpedrosa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 12:03:29 by rpedrosa          #+#    #+#             */
/*   Updated: 2025/04/17 11:32:45 by rpedrosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"
#include "../../incs/parsing.h"
/* @brief: counts the number of arguments saved in the current table
	@return: number of arguments counted */
int	count_args(t_simple_command *curr_table)
{
	int	i;

	i = 0;
	while (curr_table->args[i])
		i++;
	return (i);
}
/* @brief: counts the number of chars s will have after we deletes the quotes
			needed to alloc space for the new altered string
	@return: len of the new string */
int after_quotes_strlen(char *s)
{
	int	i;
	int quote_skipped;

	quote_skipped = 0;
	i = 0;
	if (s)
	{
		while (s[i])
		{
			if (s[i] == 34 || s[i] == 39)
			{
				i += skip_quotes(s, i);
				quote_skipped += 2;
			}
			if (s[i])
				i++;
		}
	}
	return (i - quote_skipped);
}
/* @brief: counts the len of s after A and B are deleted
	@return: the len counted */
int	after_sig_strlen(char	*s, char A, char B)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (s)
	{
		while (s[i])
		{
			if (s[i] == A || s[i] == B)
				count = skip_quotes(s, i);
			if (s[i] != A && s[i] != B)
				count++;
			i++;
		}
	}
	return (count);
}
/* @brief: checks if a char is a whitespace
	@return: 1 if it is
			 0 if it is not */
int	ft_isspace(char c)
{
	if (c == 32 || (c >= 9 && c <= 13))
		return (1);
	return (0);
}
/* @brief: checks if there is a pipe in the beggining or the end of the command
			if it finds any the program will give an error
	@return: 0 if it finds any
			 1 if it does not */
int	check_pipes(char *s)
{
	int	i;

	i = 0;
	while (s[i] && ft_isspace(s[i]))
		i++;
	if (s[i] == '|')
		return (0);
	while (s[i])
		i++;
	i--;
	while (ft_isspace(s[i]))
		i--;
	if (s[i] == '|')
		return (0);
	return (1);
}

