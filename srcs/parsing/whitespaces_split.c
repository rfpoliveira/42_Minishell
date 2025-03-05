/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   whitespaces_split.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpedrosa <rpedrosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 10:37:05 by rpedrosa          #+#    #+#             */
/*   Updated: 2025/03/05 15:44:22 by rpedrosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"
#include "../../incs/parsing.h"

//this is a split moddified to skip anything bettewn quotes
//39 ascii to single quote
//34 ascii for double quote
size_t skip_quotes(const char *s, size_t i)
{
	i++;
	if (s[i - 1] == 39)
	{
		while (s[i] != 39 && s[i])
			i++;
	}
	if (s[i - 1] == 34)
	{
		while (s[i] != 34 && s[i])
			i++;
	}
	return (i);
}

static size_t	r_count_sep(const char *s)
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
			i = skip_quotes(s, i);
		if (ft_isspace(s[i]) && s[i + 1] && !ft_isspace(s[i + 1]))
			count++;
		i++;
	}
	return (count);
}

static char	**fill(const char *s, char **res)
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
		if (ft_isspace(s[i]) == 0 && s[i])
		{
			while (ft_isspace(s[i]) == 0 && s[i])
			{
				if ((s[i] == 34 || s[i] == 39))
				{
					skiped = skip_quotes(s, i);
					j += skiped;
					i += skiped;
					skiped = 0;
				}
				else
				{
					j++;
					i++;
				}
			}
		}
		res[++r] = ft_substr(s, i - j, j);
		if (!res[r])
			return (matrix_free(res), NULL);
		j = 0;
		if (s[i] == '\0')
			break ;
	}
	return (res);
}

char	**whitespaces_split(const char *s)
{
	char	**result;
	size_t	count;

	count = r_count_sep(s);
	result = malloc(sizeof (char *) * (count + 1));
	if (!result)
		return (NULL);
	result = fill(s, result);
	if (!result)
		return (NULL);
	result[count] = NULL;
	return (result);
}

int	main()
{
	char	*buff = "ec'ho' $A     1 $B$C";
	char **array = whitespaces_split(buff);
	int i = 0;
    while (array[i])
	{
		printf("%s\n", array[i]);
	   	i++;
	}
	matrix_free(array);
}
