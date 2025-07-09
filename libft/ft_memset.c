/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpedrosa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 10:00:32 by rpedrosa          #+#    #+#             */
/*   Updated: 2024/10/22 10:44:03 by rpedrosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*str;

	str = b;
	while (len > 0)
	{
		*(str++) = c;
		len --;
	}
	return (b);
}
/*
#include <stdlib.h>

int	main()
{
	unsigned char* teste = malloc(6);
	
	ft_memset(teste, '5', 5);

	int i = 0;
	while (teste[i])
	{
		printf("%c", teste[i]);
		i++;
	}
}*/
