/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpedrosa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 14:02:29 by rpedrosa          #+#    #+#             */
/*   Updated: 2024/10/22 15:17:55 by rpedrosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	len_src;

	len_src = ft_strlen(src);
	if (dstsize > len_src + 1)
		ft_memcpy(dst, src, len_src + 1);
	else if (dstsize != 0)
	{
		ft_memcpy(dst, src, dstsize - 1);
		dst[dstsize - 1] = 0;
	}
	return (len_src);
}
/*
int	main()
{
	char *buff = "coucou";
	char *source = "AAAAAAAAAAA";

	int i = ft_strlcpy (buff, source, 0);

	printf("%s %i\n", buff, i);

	char *buff2 = "coucou";
        char *source2 = "AAAAAAAAAAA";

        int y = strlcpy(buff2, source2, 0);
	printf("%s %i\n", buff2, y);
}*/
