/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpedrosa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 10:09:56 by rpedrosa          #+#    #+#             */
/*   Updated: 2024/10/23 16:41:26 by rpedrosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*temps1;
	unsigned char	*temps2;

	temps1 = (unsigned char *)s1;
	temps2 = (unsigned char *)s2;
	while (n > 0)
	{
		if (*temps1 != *temps2)
			return (*temps1 - *temps2);
		temps1++;
		temps2++;
		n--;
	}
	return (0);
}
/*
int	main()
{
	char *buff = "ze";
	char *buff2 = "";
	int n = 3;

	int i = ft_memcmp(buff, buff2, n);
	int y = memcmp(buff, buff2, n);

	printf("mine: %i, og: %i", i , y);
}
*/
