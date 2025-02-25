/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpedrosa <rpedrosa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 10:37:05 by rpedrosa          #+#    #+#             */
/*   Updated: 2025/02/20 16:05:12 by rpedrosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

//this is a split moddified to skip anything bettewn quotes
//39 ascii to single quote
//34 ascii for double quote
static size_t skip_quotes(const char *s, size_t i)
{
	i++;
	if (s[i] == 39)
	{
		while (s[i] != 39 && s[i])
			i++;
	}
	if (s[i] == 34)
	{
		while (s[i] != 34 && s[i])
			i++;
	}
	return (i);
}

static size_t	r_count_sep(const char *s, char sep)
{
	size_t	i;
	size_t	count;
	int	quote;

	quote = 0;
	count = 0;
	i = 0;
	if (!s)
		return (count);
	if (s[i] != sep)
		count++;
	while (s[i])
	{
		if ((s[i] == 34 || s[i] == 39) && quote == 0)
		{
			i = skip_quotes(s, i);
			quote = 1;
		}
		else if ((s[i] == 34 || s[i] == 39) && quote == 1)
			quote = 0;
		else if (s[i] == sep && s[i + 1] && s[i + 1] != sep)
			count++;
		i++;
	}
	printf("%ld\n", count);
	return (count);
}

static char	**fill(const char *s, char **res, char c)
{
	int		j;
	int		r;
	int		i;
	int	skiped;
	int quote;

	i = -1;
	j = 0;
	skiped = 0;
	r = -1;
	quote = 0;
	while (s[++i])
	{
		if (s[i] != c)
		{
			while (s[i] != c && s[i] && quote == 0)
			{
				if ((s[i] == 34 || s[i] == 39) && quote == 0)
				{
					skiped = skip_quotes(s, i);
					j += skiped;
					i += skiped;
					skiped = 0;
					quote = 1;
				}
				else if ((s[i] == 34 || s[i] == 39) && quote == 1)
					quote = 0;
				j++;
				i++;
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

char	**parsing_split(const char *s, char c)
{
	char	**result;
	size_t	count;

	count = r_count_sep(s, c);
	result = malloc(sizeof (char *) * (count + 1));
	if (!result)
		return (NULL);
	result = fill(s, result, c);
	if (!result)
		return (NULL);
	result[count] = NULL;
	return (result);
}
/*
int	main()
{
	char	*buff = "echo $A'   $B'$C";
	char buff2 = ' ';
	char **array = parsing_split(buff, buff2);
	int i = 0;
    while (array[i])
	{
		printf("%s\n", array[i]);
	   	i++;
	}
	matrix_free(array);
	ft_split(buff, buff2);
}*/
