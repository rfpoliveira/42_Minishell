/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils4.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpedrosa <rpedrosa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 11:57:07 by rpedrosa          #+#    #+#             */
/*   Updated: 2025/06/11 17:11:13 by rpedrosa         ###   ########.fr       */
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
	/*printf("j: %i\n", (*j));*/
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
void red_order_code(int count, char *command, t_simple_command *curr_table)
{
	int		i;
	int		j;
	char	*tmp;

	i = -1;
	j = 0;
	/*printf("command: %s\n", command);*/
	tmp = malloc(sizeof(char) * count + 1);
	tmp[count] = '\0';
	while (command[++i] && j != count)
		symbol_checker(tmp, command, &i, &j);
	curr_table->red_order = ft_strdup(tmp);
	free(tmp);
}
