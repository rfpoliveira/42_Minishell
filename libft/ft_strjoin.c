/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpedrosa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 12:17:45 by rpedrosa          #+#    #+#             */
/*   Updated: 2024/10/24 14:31:08 by rpedrosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	unsigned int	i;
	unsigned int	y;
	unsigned char	*joint;

	i = 0;
	y = 0;
	if (!s1)
		return ((char *)s2);
	if (!s2)
		return ((char *)s1);
	joint = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (joint == NULL)
		return ((char *)joint);
	while (s1[i])
	{
		joint[i] = s1[i];
		i++;
	}
	while (s2[y])
	{
		joint[i++] = s2[y];
		y++;
	}
	joint[i] = '\0';
	return ((char *)joint);
}
/*
int	main ()
{
	char *buff = "hello ";
	char *buff2 = "world!";
	printf("%s", ft_strjoint(buff, buff2));
}*/
