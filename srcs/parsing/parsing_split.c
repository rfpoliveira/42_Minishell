/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpedrosa <rpedrosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 10:42:07 by rpedrosa          #+#    #+#             */
/*   Updated: 2025/03/06 11:42:27 by rpedrosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"
#include "../../incs/parsing.h"

//this is a split moddified to skip anything bettewn quotes
//39 ascii to single quote
//34 ascii for double quote

static void	substring_calc(char *s, int *i, int *j, int *skiped, char sep)
{
	while (s[*i] != sep && s[*i])
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

static char	**fill(char *s, char **res, char sep)
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
		if (s[i] != sep)
		{
			substring_calc(s, &i, &j, &skiped, sep);
		if (r == -1)
			res[++r] = ft_substr(s, i - j, j);
		else
			res[++r] = ft_substr(s, i - j - 1, j + 1);
		if (!res[r])
			return (matrix_free(res), NULL);
		j = 0;
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

/* int	main()
{
	char	*buff = "|ola|adeus '| pronto 1'";
	char **array = parsing_split(buff, '|');
	int i = 0;
    while (array[i])
	{
		printf("%s\n", array[i]);
	   	i++;
	}
	matrix_free(array);
} */