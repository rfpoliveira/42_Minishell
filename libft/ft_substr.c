/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpedrosa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 11:39:55 by rpedrosa          #+#    #+#             */
/*   Updated: 2024/10/24 12:15:51 by rpedrosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned char	*sub;
	unsigned int	stringlen;
	unsigned int	i;

	i = 0;
	if (!s)
		return (NULL);
	stringlen = ft_strlen(s);
	if (start > stringlen)
		return (ft_calloc(1, 1));
	if (stringlen - start < len)
		sub = malloc (stringlen - start + 1);
	else
		sub = malloc(len + 1);
	if (!sub)
		return (NULL);
	while (s[start] && (i < len))
	{
		sub[i] = s[start];
		i++;
		start++;
	}
	sub[i] = '\0';
	return ((char *)sub);
}
/*
int	main()
{
	char *buff = "olatudobom";
	int i = 2;
	int y = 5;
	char	*dup = ft_substr(buff, i , y);
	printf("%s", dup);
	free(dup);
}*/
