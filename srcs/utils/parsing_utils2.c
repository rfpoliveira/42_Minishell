/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpedrosa <rpedrosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 12:03:29 by rpedrosa          #+#    #+#             */
/*   Updated: 2025/03/28 14:35:40 by rpedrosa         ###   ########.fr       */
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
