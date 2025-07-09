/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpedrosa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 17:30:43 by rpedrosa          #+#    #+#             */
/*   Updated: 2024/10/22 17:45:12 by rpedrosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	tempc;

	tempc = (unsigned char)c;
	i = 0;
	while (s[i])
	{
		if (s[i] == tempc)
			return ((char *)&s[i]);
		i++;
	}
	if (s[i] == tempc)
		return ((char *)&s[i]);
	return (0);
}
/*
int main ()
{
	char *buff = ft_strchr("hello", '\0');
	printf("ft: %s", buff);

	char *buff2 = strchr("hello", '\0');
	printf("og: %s", buff2);
}*/
