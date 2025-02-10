/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpedrosa <rpedrosa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 16:50:50 by rpedrosa          #+#    #+#             */
/*   Updated: 2025/02/10 17:46:06 by rpedrosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

void set_single_command(t_command *command, char **s, int number_args, int index)
{
	t_simple_command *simple;
	int	i;

	i = 0;
	command->table[command->number_simple_commands - 1] = simple;
	simple->number_args = number_args;
	while(number_args > 0)
	{
		simple->args[i] = ft_strdup(s[index - number_args]);
		number_args--;
		i++;
	}
	simple->args[i] = NULL;
	if (ft_strncmp(s[index], "<", 2) == 0)
		command->infile = ft_strdup(s[index + 1]);
	if (ft_strncmp(s[index], ">", 2) == 0)
		command->outfile = ft_strdup(s[index + 1]);
}

void  expande(char *sub)
{
	sub = get_env(sub + 1);
}

void  create_table(t_command *command, char **splited)
{
	int	i;
	int j;

	i = 0;
	j = 0;
	while(splited[i])
	{
		if (splited[i][0] == '$')
			expande(splited[i]);
		if (ft_strncmp(splited[i], "|", 2) == 0 || ft_strncmp(splited[i], ">>", 3) == 0 || \
				ft_strncmp(splited[i], "<<", 3) == 0 || ft_strncmp(splited[i], ">", 2) == 0 || \
				ft_strncmp(splited[i], "<", 2) == 0)
		{
			set_single_command(command, splited, i - j, i);
			j = i;
			command->number_simple_commands++;
		}
		i++;
	}
}

t_command parsing(t_command *command, char *s)
{
	char **splited;

	splited = ft_split(s, ' ');
	create_table(command, splited);	
}
