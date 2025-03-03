/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpedrosa <rpedrosa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 15:25:40 by rpedrosa          #+#    #+#             */
/*   Updated: 2025/02/25 15:31:59 by rpedrosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

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

/*static int	parse_file(char *s)
{
	if (s[3] == '<' || s[3] == '>')
		return (print_error(SYNTAX_ERROR));
}

static int	in_outfile_quotes(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	if (parse_file(s) != 0)
		return (SYNTAX_ERROR);
}*/

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
