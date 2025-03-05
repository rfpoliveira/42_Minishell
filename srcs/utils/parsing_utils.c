/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpedrosa <rpedrosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 15:25:40 by rpedrosa          #+#    #+#             */
/*   Updated: 2025/03/05 15:14:00 by rpedrosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/parsing.h"
#include "../../incs/minishell.h"

static int	after_quote_strlen(char	*s)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (s)
	{
		while (s[i])
		{
			if (s[i] != 34 && s[i] != 39)
				count++;
			i++;
		}
	}
	return (count);
}

static void  delete_quotes(char *s)
{
	int	i;
	char*  temp;
	int	len;

	i = 0;
	len = after_quote_strlen(s);
	temp = malloc(len + 1);
	temp[len] = '\0';
	len = 0;
	while (s[i])
	{
		if (s[i] != 34 && s[i] != 39)
		{
			temp[len] = s[i];
			len++;
		}
		i++;
	}
	ft_strlcpy(s, temp, len + 1);
	free(temp);
}
int	ft_isspace(char c)
{
	if (c == 32 || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

int  handle_quotes(t_command *command)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while(command->table[i])
	{
	/*	if (in_outfile_quotes(command->table[i]->infile) != 0)
			return (SYNTAX_ERROR);
		if (in_outfile_quotes(command->table[i]->outfile)
			return (SYNTAX_ERROR);
		}*/
		while(command->table[i]->args[j])
		{
			delete_quotes(command->table[i]->args[j]);
			j++;
		}
		j = 0;
		i++;
	}
	return (0);
}
