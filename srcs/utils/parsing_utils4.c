/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils4.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpedrosa <rpedrosa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 11:57:07 by rpedrosa          #+#    #+#             */
/*   Updated: 2025/07/09 15:23:51 by rpedrosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

static void	symbol_checker(char *tmp, char *command, int *i, int *j)
{
	if (command[*i] == '>')
	{
		if (command[*i + 1] != '>')
			tmp[(*j)++] = '2';
		else
			tmp[(*j)++] = '4';
		(*i)++;
	}
	if (command[*i] == '<')
	{
		if (command[*i + 1] != '<')
			tmp[(*j)++] = '1';
		else
			tmp[(*j)++] = '3';
		(*i)++;
	}
}

/**
 @brief stores a code that indicates the order of the redirects
  
	1 represents infiles,
	2 represents outfiles,
	3 represents double_infiles,
	4 represents double_outfiles

 @param table is the current table being checked
 @param command is the arguments of the current table
 @param code is where the code will be stored
*/
void	red_order_code(int count, char *command, t_simple_command *curr_table)
{
	int		i;
	int		j;
	char	*tmp;

	i = -1;
	j = 0;
	tmp = malloc(sizeof(char) * count + 1);
	tmp[count] = '\0';
	while (command[++i] && j != count)
		symbol_checker(tmp, command, &i, &j);
	curr_table->red_order = ft_strdup(tmp);
	ft_free(&tmp);
}

void	iter(char c, int *chr)
{
	if (c && c != 34 && c != 39)
		(*chr)++;
}

int	check_arg_red(int j, int i, int lsx, char **cur)
{
	if ((j != 0 && i == 0) || \
(j != 0 && cur[i][j] == '>' && \
(cur[i - 1][lsx] != '<' && cur[i - 1][lsx] != '>')) || \
(j != 0 && cur[i][j] == '<' && \
(cur[i - 1][lsx] != '<' && cur[i - 1][lsx] != '>')) || \
(!cur[i][j] && (cur[i - 1][lsx] != '<' && cur[i - 1][lsx] != '>')))
		return (1);
	return (0);
}
