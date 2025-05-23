/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   whitespaces_split.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpedrosa <rpedrosa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 10:37:05 by rpedrosa          #+#    #+#             */
/*   Updated: 2025/05/23 13:59:03 by rpedrosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"
#include "../../incs/parsing.h"

/** 
 @brief calculates from where to where we need copy the string 
		to get whats bettewn separators
 @param s is the string to split;
 @param sep is the char we will use to make the separacion 
			(is not kept in the return);
 @param i is the current char;
 @param j is the len of the string we will copy;
 @note ignores whats bettewn quotes or double quotes (skip_quotes),
			39 ascii to single quote and 34 ascii for double quote 
*/
static void	substring_calc(char *s, int *i, int *j, int *skiped)
{
	while (ft_isspace(s[*i]) == 0 && s[*i])
	{
		if ((s[*i] == 34 || s[*i] == 39))
		{
			*skiped = skip_quotes(s, *i);
			*j += *skiped;
			*i += *skiped;
			*skiped = 0;
		}
		else
		{
			(*j)++;
			(*i)++;
		}
	}
}

/**
 @brief populates the matrix with the smaller strings 
		that are suposed to be separated.

	iterates threw all s ultil it finds a separator
	uses substring to create a copy of whats not a 
	separator until then and put it in the matrix

 @param s is the string to be separeted;
 @param res is the poiter to the first element of the matrix 
		    to be populated;
 @return the allocated matrix with the pointers to the smaller 
		 allocated strings in each index,
		 NULL of errors OF memory allocacion 
*/
static char	**fill(char *s, char **res)
{
	int		j;
	int		r;
	int		i;
	int		skiped;

	i = -1;
	j = 0;
	skiped = 0;
	r = -1;
	while (s[++i])
	{
		if (ft_isspace(s[i]) == 0)
		{
			substring_calc(s, &i, &j, &skiped);
			res[++r] = ft_substr(s, i - j, j);
			if (!res[r])
				return (matrix_free(res), NULL);
			j = 0;
		}
		if (s[i] == '\0')
			break ;
	}
	return (res);
}

/**
 @brief seperate a string into many.
 
	the separators will be all whitespaces 
	(32 and bettewn 9 and 13 in ascii, inclusively)
	first it counts how many string we will end up with (r_count_whitespaces)
	allocate memory for the pointer array or matrix
	populates the matrix (fill)

 @param s is the string to split.
 @note ignores whats in quotes or double quotes 
	(while in them the all of it is suposed to be literal)
 @return a allocated matrix correctly sperated in case of sucess,
		 NULL in case of errors 
*/
char	**whitespaces_split(char *s)
{
	char	**result;
	size_t	count;

	count = r_count_whitespaces(s);
	result = malloc(sizeof(char *) * (count + 1));
	if (!result)
		return (NULL);
	result = fill(s, result);
	if (!result)
		return (NULL);
	result[count] = NULL;
	return (result);
}
