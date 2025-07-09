/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpedrosa <rpedrosa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 14:02:11 by rpedrosa          #+#    #+#             */
/*   Updated: 2024/10/25 15:03:39 by rpedrosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(const char *s, char (*f)(unsigned int, char))
{
	int		i;
	char	*result;

	result = ft_strdup(s);
	if (!result)
		return (NULL);
	i = 0;
	while (result[i])
	{
		result[i] = (*f)(i, result[i]);
		i++;
	}
	return (result);
}
/*
char	r_tolower(unsigned int i, char c)
{
	i = 0;
	if (c >= 'A' && c <= 'Z')
		return (c + 32);
	return (c);
}

int	main (void)
{
	int i = 0;
	char *buff = "HELLO";
	char *buff2 = ft_strmapi(buff,r_tolower);
	printf("%s", buff2);
}*/
