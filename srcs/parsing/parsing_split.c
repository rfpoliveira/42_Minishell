/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpedrosa <rpedrosa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 10:42:07 by rpedrosa          #+#    #+#             */
/*   Updated: 2025/03/20 14:56:13 by rpedrosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"
#include "../../incs/parsing.h"

//this is a split moddified to skip anything bettewn quotes
//39 ascii to single quote
//34 ascii for double quote

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
			if (r == -1)
				res[++r] = ft_substr(s, i - j, j);
			else
				res[++r] = ft_substr(s, i - j - 1, j + 1);
			if (!res[r])
				return (matrix_free(res), NULL);
		}
		if (s[i] == '\0')
			break ;
	}
	if (s[i - 1] == sep)
		res[++r] = ft_substr(s, i - 1, 1);
	return (res);
}

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
