/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpedrosa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 17:48:33 by rpedrosa          #+#    #+#             */
/*   Updated: 2024/10/22 18:12:59 by rpedrosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int				i;
	unsigned char	tempc;

	i = 0;
	tempc = (unsigned char)c;
	while (s[i])
		i++;
	while (i >= 0)
	{
		if (s[i] == tempc)
			return ((char *)&s[i]);
		i--;
	}
	if (*s == tempc)
		return ((char *)&s[i]);
	return (0);
}
/*
int main ()
{
       char *buff = ft_strrchr("123456789", a);
        printf("ft: %s", buff);

        char *buff2 = strrchr("123456789", a);
        printf("og: %s", buff2);
}*/
