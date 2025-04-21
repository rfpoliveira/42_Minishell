/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpedrosa <rpedrosa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 10:30:51 by rpedrosa          #+#    #+#             */
/*   Updated: 2025/04/21 19:36:47 by rpedrosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"
#include "../../incs/parsing.h"

/* @brief: it is called when a quote is found and it skippes until the one that closes it 
	@arguments: s is the current string we are interating threw
				i is the index next to the quote
	@return: it returns the number of char we skipping because there are in the middle of quotes
*/

size_t	skip_quotes(char *s, size_t i)
{
	int	skiped;

	skiped = 1;
	i++;
	if (s[i - 1] == 39)
	{
		while (s[i] != 39 && s[i])
		{
			i++;
			skiped++;
		}
	}
	if (s[i - 1] == 34)
	{
		while (s[i] != 34 && s[i])
		{
			skiped++;
			i++;
		}
	}
	if (s[i])
		skiped++;
	return (skiped);
}
/* @brief: word count for the whitespacs split 
	@notes: it skips anything bettewn quotes
	@return: the number of "words" separated by whitespaces in a string 
*/

size_t	r_count_whitespaces(char *s)
{
	size_t	i;
	size_t	count;

	count = 0;
	i = 0;
	if (!s)
		return (count);
	if (!ft_isspace(s[i]))
		count++;
	while (s[i])
	{
		if ((s[i] == 34 || s[i] == 39))
			i += skip_quotes(s, i);
		if (ft_isspace(s[i]) && s[i + 1] && !ft_isspace(s[i + 1]))
			count++;
		i++;
	}
	return (count);
}
/* @brief: word count for the parsing split 
	@arguments: s is the string being checked
				sep is the separator used 
	@notes: it skips anything bettewn quotes
	@return: the number of "words" separated by sep in a string 
*/

size_t	r_count_sep(char *s, char sep)
{
	size_t	i;
	size_t	count;

	count = 0;
	i = 0;
	if (!s)
		return (count);
	if (s[i] != sep && s[i] != '\0')
		count++;
	while (s[i])
	{
		if ((s[i] == 34 || s[i] == 39))
			i += skip_quotes(s, i);
		if (s[i] == sep && s[i + 1] != sep)
			count++;
		i++;
	}
	return (count);
}
