/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftprint.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpedrosa <rpedrosa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 16:44:52 by rpedrosa          #+#    #+#             */
/*   Updated: 2024/11/06 16:47:43 by rpedrosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXTRA_H
# define EXTRA_H

# include "../libft.h"
# include <stdarg.h>

int		ft_printf(const char *format, ...);
int		r_putnbr(int n);
int		r_put_hex(unsigned int n, char c);
int		r_putstr(char *s);
int		r_putunsig(unsigned int n);
int		r_put_ptr(unsigned long long n);
char	*get_next_line(int fd);
char	*get_next_line_fd(int fd);
void	r_free(char **ptr);
void	matrix_free(char **mtx);

#endif
