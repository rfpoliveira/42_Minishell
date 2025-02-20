/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpedrosa <rpedrosa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 11:26:32 by rpedrosa          #+#    #+#             */
/*   Updated: 2025/02/20 16:26:40 by rpedrosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

//expandes env variables from the arguments
static char	*r_expander(char *s)
{
	int	ex_flag;
	char **buff;
	int	i;
	int	j;

	i = 0;
	j = 0;
	ex_flag = 0;
	if (!s)
		return (NULL);
	if (s[0] == '$')
		ex_flag = 1;
	buff = ft_split(s, '$');
	s = NULL;
	while (buff[i])
		i++;
	if (ex_flag == 1)
		s = getenv(buff[0]);
	else 
		s = ft_strdup(buff[0]);
	while (++j < i)
		s = ft_strjoin(s, getenv(buff[j]));
	matrix_free(buff);
	return (s);
}

//will take quotes out and expand if it needs to
//39 ascii to single quote
//34 ascii for double quote
void  r_quote_handler(t_simple_command *table)
{
	char **arg;
	int	i;
	int j;

	j = -1;
	i = -1;
	arg = table->args;
	while (arg[++i])
	{
		while (arg[i][++j])
		{
			if (arg[i][j++] == 39)
				while(arg[i][j] != 39 && arg[i][j])
					j++;
			if (arg[i][j] == '$')
				arg[i] = r_expander(arg[i]);
		}
		j = 0;
	}
}
