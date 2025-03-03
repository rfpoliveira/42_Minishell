/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpedrosa <rpedrosa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 11:45:02 by rpedrosa          #+#    #+#             */
/*   Updated: 2025/03/03 11:45:06 by rpedrosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

static void	change_arg(char **arg, int arg_pos, int flag)
{
	int	i;
	char  *temp;

	i = arg_pos;
	temp = NULL;
	if (arg[arg_pos + flag] == NULL)
	{
		ft_free(&arg[arg_pos]);
		if (flag == 2)
			ft_free(&arg[arg_pos + 1]);
	}
	else 
	{
		i += flag;
		while (arg[i])
		{
			ft_free(&arg[i - flag]);
			arg[i - flag] = ft_strdup(arg[i]);
			ft_free(&arg[i]);
			i++;
		}
		ft_free(&arg[i - flag]);
	}
}

static void recount_args(t_simple_command *simple_command)
{
	int	i;

	i = 0;
	while (simple_command->args[i])
		i++;
	simple_command->number_args = i;
}

static void do_outfile(char *buff, int i, t_command *command, int table_pos, int arg_pos)
{
	if (buff[i + 1] == '\0' || (buff[i + 1] == '>' && buff[i + 2] == '\0'))
	{
		command->table[table_pos]->outfile = ft_strjoin(buff, command->table[table_pos]->args[arg_pos + 1]);
		change_arg(command->table[table_pos]->args, arg_pos, 2);
	}
	else
	{
		command->table[table_pos]->outfile = ft_strdup(buff + i);
		change_arg(command->table[table_pos]->args, arg_pos, 1);
	}
	recount_args(command->table[table_pos]);
}

static void do_infile(char *buff, int i, t_command *command, int table_pos, int arg_pos)
{
	if (buff[i + 1] == '\0' || (buff[i + 1] == '<' && buff[i + 2] == '\0'))
	{
		command->table[table_pos]->infile = ft_strjoin(buff, command->table[table_pos]->args[arg_pos + 1]);
		change_arg(command->table[table_pos]->args, arg_pos, 2);
	}	
	else
	{
		command->table[table_pos]->infile = ft_strdup(buff + i);
		change_arg(command->table[table_pos]->args, arg_pos, 1);
	}
	recount_args(command->table[table_pos]);
}

void assign_redirect(t_command *command, int table_pos, int	arg_pos)
{
	size_t	i;
	char *buff;

	i = 0;
	buff = command->table[table_pos]->args[arg_pos];
	while (buff[i])
	{
		if (buff[i] == 34 || buff[i] == 39)
			i = skip_quotes(buff, i);
		if (buff[i] == '>')
			do_outfile(buff, i, command, table_pos, arg_pos);
		if (buff[i] == '<')
			do_infile(buff, i, command, table_pos, arg_pos);
		i++;
	}
}
