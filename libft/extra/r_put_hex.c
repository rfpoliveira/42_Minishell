/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_putpointer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpedrosa <rpedrosa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 17:15:50 by rpedrosa          #+#    #+#             */
/*   Updated: 2024/11/07 17:33:17 by rpedrosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "extra.h"

static void	r_print_hex(unsigned int n, char c);
static int	r_count_hex(unsigned int n);

int	r_put_hex(unsigned int n, char c)
{
	r_print_hex(n, c);
	return (r_count_hex(n));
}

static int	r_count_hex(unsigned int n)
{
	int	count;

	count = 0;
	if (n == 0)
		return (1);
	while (n > 0)
	{
		n /= 16;
		count++;
	}
	return (count);
}

static void	r_print_hex(unsigned int n, char c)
{
	unsigned char	digit;

	if (n >= 16)
	{
		r_print_hex((n / 16), c);
		r_print_hex((n % 16), c);
	}
	else
	{
		if (n < 10)
			digit = n + '0';
		else if (c == 'x')
			digit = n + 'a' - 10;
		else
			digit = n + 'A' - 10;
		write(1, &digit, 1);
	}
}
/*
int	main ()
{
	char *s = "hello";
	r_put_hex(s, 'p');
	write(1, "\n",1);
	r_put_hex(0x124fa, 'x');
	write(1, "\n",1);
	r_put_hex(0x124fa, 'X');


	printf("\n%p %x %X", &s, 0x123fa, 0x123fa);
}*/
