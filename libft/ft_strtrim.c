/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpedrosa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 13:46:13 by rpedrosa          #+#    #+#             */
/*   Updated: 2024/10/24 16:30:12 by rpedrosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*r_trim_beg(char *s1, char *set)
{
	int	i;
	int	j;
	int	b;

	i = 0;
	j = 0;
	b = 0;
	while (s1[i])
	{
		while (set[j])
		{
			if (set[j++] == s1[i])
			{
				b = 1;
				break ;
			}
		}
		if (b == 0)
			break ;
		b = 0;
		j = 0;
		i++;
	}
	return (s1 + i);
}

static int	r_trim_end(char *s1, char *set)
{
	int	i;
	int	j;
	int	b;

	i = 0;
	j = 0;
	b = 0;
	while (s1[i])
		i++;
	while (--i > 0)
	{
		while (set[j])
		{
			if (set[j++] == s1[i])
			{
				b = 1;
				break ;
			}
		}
		if (b == 0)
			break ;
		b = 0;
		j = 0;
	}
	return (i);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		len;
	char	*trimed;

	s1 = r_trim_beg((char *)s1, (char *)set);
	len = r_trim_end ((char *)s1, (char *)set);
	trimed = malloc (len + 2);
	if (trimed == NULL)
		return (trimed);
	trimed = ft_memmove(trimed, s1, len + 1);
	trimed[len + 1] = '\0';
	return (trimed);
}
/*
int	main()
{
	char *buff = ft_strtrim("virusprogramvirus", "virus");
	printf("%s", buff);
}*/
