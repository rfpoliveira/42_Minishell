/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpedrosa <rpedrosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 10:30:51 by rpedrosa          #+#    #+#             */
/*   Updated: 2025/04/04 14:35:30 by rpedrosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"
#include "../../incs/parsing.h"

//skips anything bettewn quotes and returns how many chars were skiped
size_t	skip_quotes(char *s, size_t i)
{
	int	skiped;

	skiped = 1;
	i++;
	if (s[i - 1] == 39)
	{
		while (s[i] != 39 && s[i])
		{
			i++;
			skiped++;
		}
	}
	if (s[i - 1] == 34)
	{
		while (s[i] != 34 && s[i])
		{
			skiped++;
			i++;
		}
	}
	if (s[i])
		skiped++;
	return (skiped);
}
//word count for the whitespacs split
size_t	r_count_whitespaces(char *s)
{
	size_t	i;
	size_t	count;

	count = 0;
	i = 0;
	if (!s)
		return (count);
	if (!ft_isspace(s[i]))
		count++;
	while (s[i])
	{
		if ((s[i] == 34 || s[i] == 39))
			i += skip_quotes(s, i);
		if (ft_isspace(s[i]) && s[i + 1] && !ft_isspace(s[i + 1]))
			count++;
		i++;
	}
	return (count);
}
//word count for the parsing split
size_t	r_count_sep(char *s, char sep)
{
	size_t	i;
	size_t	count;

	count = 0;
	i = 0;
	if (!s)
		return (count);
	if (s[i] != sep && s[i] != '\0')
		count++;
	while (s[i])
	{
		if ((s[i] == 34 || s[i] == 39))
			i += skip_quotes(s, i);
		if (s[i] == sep && s[i + 1] != sep)
			count++;
		i++;
	}
	return (count);
}
