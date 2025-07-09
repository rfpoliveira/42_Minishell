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

static void	r_print_ptr(unsigned long long n);
static int	r_count_ptr(unsigned long long n);

int	r_put_ptr(unsigned long long n)
{
	if (n == 0)
	{
		write (1, "(nil)", 5);
		return (5);
	}
	write(1, "0x", 2);
	r_print_ptr(n);
	return (r_count_ptr(n));
}

static int	r_count_ptr(unsigned long long n)
{
	int	count;

	count = 2;
	while (n > 0)
	{
		n /= 16;
		count++;
	}
	return (count);
}

static void	r_print_ptr(unsigned long long n)
{
	unsigned char	digit;

	if (n >= 16)
	{
		r_print_ptr((n / 16));
		r_print_ptr((n % 16));
	}
	else
	{
		if (n < 10)
			digit = n + '0';
		else
			digit = n + 'a' - 10;
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
