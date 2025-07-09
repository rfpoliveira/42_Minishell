/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpedrosa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 11:23:40 by rpedrosa          #+#    #+#             */
/*   Updated: 2024/10/22 12:10:49 by rpedrosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*temp_dest;
	unsigned char	*temp_src;

	if (src == 0 && dst == 0)
		return (dst);
	temp_dest = dst;
	temp_src = (unsigned char *)src;
	while (n > 0)
	{
		*(temp_dest++) = *(temp_src++);
		n--;
	}
	return (dst);
}
/*
int	main()
{
	char buff[6] = "Hello7";
	char copia[6] = "copia.";

	ft_memcpy(buff, copia, 5);
	printf("%s", buff);
}*/
