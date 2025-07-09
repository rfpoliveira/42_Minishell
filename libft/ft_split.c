/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpedrosa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 16:32:56 by rpedrosa          #+#    #+#             */
/*   Updated: 2024/10/25 11:13:40 by rpedrosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	r_count_sep(const char *s, char sep)
{
	size_t	i;
	size_t	count;

	count = 0;
	i = 0;
	if (s[i] != sep && s[i] != '\0')
		count++;
	while (s[i])
	{
		if (s[i] == sep && s[i + 1] != '\0' && s[i + 1] != sep)
			count++;
		i++;
	}
	return (count);
}

static	void	*ft_free(char	**s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		free(s[i]);
		i++;
	}
	free(s);
	return (NULL);
}

static char	**fill(const char *s, char **res, char c)
{
	int		j;
	int		r;
	int		i;

	i = -1;
	j = 0;
	r = -1;
	while (s[++i])
	{
		if (s[i] != c)
		{
			while (s[i] != c && s[i])
			{
				j++;
				i++;
			}
			res[++r] = ft_substr(s, i - j, j);
			if (!res[r])
				return (ft_free(res));
			j = 0;
		}
		if (s[i] == '\0')
			break ;
	}
	return (res);
}

char	**ft_split(const char *s, char c)
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
	char	*buff = "babnnas";
	char buff2 = ' ';
	char **array = ft_split(buff, buff2);
	int i = 0;
    while (array[i])
	{
		printf("%s\n", array[i]);
	   	i++;
	}
	ft_free(array);
	ft_split(buff, buff2);
}*/
