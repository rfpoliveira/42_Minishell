/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpedrosa <rpedrosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 12:03:29 by rpedrosa          #+#    #+#             */
/*   Updated: 2025/04/03 16:10:44 by rpedrosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"
#include "../../incs/parsing.h"

//counts the arguments present in the command passed
int	count_args(t_simple_command *simple)
{
	int	i;

	i = 0;
	while (simple->args[i])
		i++;
	return (i);
}

int after_quotes_strlen(char *s)
{
	int	i;
	int quote_skipped;

	quote_skipped = 0;
	i = 0;
	if (s)
	{
		while (s[i])
		{
			if (s[i] == 34 || s[i] == 39)
			{
				i += skip_quotes(s, i);
				quote_skipped += 2;
			}
			if (s[i])
				i++;
		}
	}
	return (i - quote_skipped);
}
//strlen but ignore A and B
int	after_sig_strlen(char	*s, char A, char B)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (s)
	{
		while (s[i])
		{
			if (s[i] == A || s[i] == B)
				count = skip_quotes(s, i);
			if (s[i] != A && s[i] != B)
				count++;
			i++;
		}
	}
	return (count);
}

int	ft_isspace(char c)
{
	if (c == 32 || (c >= 9 && c <= 13))
		return (1);
	return (0);
}
//check if the first thing in the command is a pipe
int	check_pipes(char *s)
{
	int	i;

	i = 0;
	while (s[i] && ft_isspace(s[i]))
		i++;
	if (s[i] == '|')
		return (0);
	while (s[i])
		i++;
	i--;
	while (ft_isspace(s[i]))
		i--;
	if (s[i] == '|')
		return (0);
	return (1);
}

