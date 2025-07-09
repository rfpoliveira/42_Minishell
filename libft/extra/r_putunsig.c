/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_putunsig.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpedrosa <rpedrosa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 10:51:52 by rpedrosa          #+#    #+#             */
/*   Updated: 2024/11/08 11:31:39 by rpedrosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "extra.h"

static unsigned int	count_digits(unsigned int n);
static char			*r_utoa(unsigned int n);

int	r_putunsig(unsigned int n)
{
	char			*s;
	unsigned int	i;

	s = r_utoa(n);
	ft_putstr_fd(s, 1);
	i = ft_strlen(s);
	free(s);
	return (i);
}

static unsigned int	count_digits(unsigned int n)
{
	unsigned int	count;

	count = 0;
	while (n > 0)
	{
		n /= 10;
		count++;
	}
	return (count);
}

static char	*r_utoa(unsigned int n)
{
	char			*result;
	unsigned int	c;
	unsigned int	i;

	c = count_digits(n);
	i = 0;
	result = malloc(c + 1);
	if (!result)
		return (NULL);
	result[i] = '0';
	if (n == 0)
		i++;
	while (n > 0)
	{
		result[--c] = (n % 10) + 48;
		n /= 10;
		i++;
	}
	result[i] = '\0';
	return (result);
}
/*
int	main(void)
{
	unsigned int i = 12345678963214;
	
}*/
