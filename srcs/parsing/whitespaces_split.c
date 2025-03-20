/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   whitespaces_split.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpedrosa <rpedrosa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 10:37:05 by rpedrosa          #+#    #+#             */
/*   Updated: 2025/03/20 14:56:19 by rpedrosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"
#include "../../incs/parsing.h"

//this is a split moddified to split every thing betteewn whitespaces and
//to skip anything bettewn quotes 
//39 ascii to single quote
//34 ascii for double quote

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

char	**whitespaces_split(char *s)
{
	char	**result;
	size_t	count;

	count = r_count_whitespaces(s);
	result = malloc(sizeof (char *) * (count + 1));
	if (!result)
		return (NULL);
	result = fill(s, result);
	if (!result)
		return (NULL);
	result[count] = NULL;
	return (result);
}
