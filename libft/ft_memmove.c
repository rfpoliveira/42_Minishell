/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpedrosa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 12:16:15 by rpedrosa          #+#    #+#             */
/*   Updated: 2024/10/22 13:03:17 by rpedrosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)

{
	unsigned char	*temp_dst;
	unsigned char	*temp_src;
	size_t			i;

	if (len == 0)
		return (dst);
	temp_dst = dst;
	temp_src = (unsigned char *)src;
	if (temp_dst == 0 && temp_src == 0)
		return (dst);
	i = 0;
	if (temp_dst > temp_src)
	{
		while (len-- > 0)
			temp_dst[len] = temp_src[len];
	}
	else
	{
		while (i < len)
		{
			temp_dst[i] = temp_src[i];
			i++;
		}
	}
	return (dst);
}
/*
int     main()
{
        char buff[6] = "Hello7";
        char copia[6] = "copia.";
	printf("%s \n", buff);

        ft_memmove(buff, copia, 4);
        printf("%s \n", buff);

	 char buff2[6] = "Hello7";
        char copia2[6] = "copia.";

        memmove(buff2, copia2, 4);
        printf("%s\n", buff2);

}*/
