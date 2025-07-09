/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpedrosa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 08:53:20 by rpedrosa          #+#    #+#             */
/*   Updated: 2024/10/23 10:06:32 by rpedrosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*temps;
	unsigned char	tempc;
	unsigned int	i;

	temps = (unsigned char *)s;
	tempc = (unsigned char)c;
	i = 0;
	while (i < n)
	{
		if (temps[i] == tempc)
			return ((void *)&temps[i]);
		i++;
	}
	return (NULL);
}
/*
int	main ()
{
	char *buff = ft_memchr("hello", 'l', 5);
	char *buff2 = memchr("hello", 'l', 5);
	printf("mine: %s, og: %s.", buff, buff2);
}*/
