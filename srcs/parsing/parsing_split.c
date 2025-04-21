/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpedrosa <rpedrosa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 10:42:07 by rpedrosa          #+#    #+#             */
/*   Updated: 2025/04/21 18:41:02 by rpedrosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"
#include "../../incs/parsing.h"

/* @brief: calculates from where to where we need copy 
			the string to get whats bettewn separators
	@arguments: s is the string to split.
				i is the current char.
				j is the len of the string we will copy
	iterates the string, ignores whats bettewn quotes 
	or double quotes (skip_quotes)
	@note: 39 ascii to single quote and 34 ascii for double quote 
*/

static void	substring_calc(char *s, int *i, int *j, char sep)
{
	int	skiped;

	skiped = 0;
	*j = 0;
	while (s[*i] != sep && s[*i])
	{
		if ((s[*i] == 34 || s[*i] == 39))
		{
			skiped = skip_quotes(s, *i);
			*j += skiped;
			*i += skiped;
			skiped = 0;
		}
		else
		{
			(*j)++;
			(*i)++;
		}
	}
}
/* @brief: populates the matrix with the smaller strings 
			that are suposed to be separated.
	@arguments: s is the string to be separeted;
				res is the poiter to the first element 
				    of the matrix to be populated;
				sep is the char we will use to make the separacion 
					(is not kept in the return);
	iterates threw all s ultil it finds a separator
	uses substring to create a copy of whats not a separator 
	until then and put it in the matrix
	@return: the allocated matrix with the pointers 
			 to the smaller allocated strings
			NULL of malloc errors 
*/

static char	**fill(char *s, char **res, char sep)
{
	int		j;
	int		r;
	int		i;

	i = -1;
	j = 0;
	r = -1;
	while (s[++i])
	{
		if (s[i] != sep)
		{
			substring_calc(s, &i, &j, sep);
			res[++r] = ft_substr(s, i - j, j);
			if (!res[r])
				return (matrix_free(res), NULL);
		}
		if (s[i] == '\0')
			break ;
	}
	return (res);
}
/* @brief: seperate a string into many
	@arguments: s is the string to split;
				sep is the char we will use to make the separacion 
				(is not kept in the return);
	first it counts how many string we will end up with (r_count_sep)
	allocate memory for the pointer array or matrix
	populates the matrix (fill)
	@note: ignores whats in quotes or double quotes 
			(while in them the all of it is suposed to be literal)
	@return: a allocated matrix correctly sperated in case of sucess
			 NULL in case of errors 
*/

char	**parsing_split(char *s, char sep)
{
	char	**result;
	size_t	count;

	count = r_count_sep(s, sep);
	result = malloc(sizeof (char *) * (count + 1));
	if (!result)
		return (NULL);
	result = fill(s, result, sep);
	if (!result)
		return (NULL);
	result[count] = NULL;
	return (result);
}
