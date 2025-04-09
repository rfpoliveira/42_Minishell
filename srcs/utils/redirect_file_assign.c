/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_file_assign.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpedrosa <rpedrosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 15:07:30 by rpedrosa          #+#    #+#             */
/*   Updated: 2025/04/09 16:11:18 by rpedrosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"
#include "../../incs/parsing.h"

int	assign_util_infile(t_data *command, int arg, int table, int chr)
{
	int i;
	char **tmp;
	char **file;

	file = command->table[table]->infile;
	i = 0;
	while (file[i])
		i++;
	if (file[chr + 1] == '\0')
	{
		tmp = parsing_split(command->table[arg]->args[arg + 1], '<');
		file[i] = ft_strdup(tmp[0]);
	}
	else if (chr == 0)
	{
		tmp = parsing_split(command->table[arg]->args[arg], '<');
		file[i] = ft_strdup(tmp[0]);
	}
	else
	{
		tmp = parsing_split(command->table[arg]->args[arg], '<');
		file[i] = ft_strdup(tmp[1]);
	}
	file[i + 1] = NULL;
	return (free(tmp), 0);
}

int	assign_util_outfile(t_data *command, int arg, int table, int chr)
{
	int i;
	char **tmp;
	char **file;

	file = command->table[table]->outfile;
	i = 0;
	while (file[i])
		i++;
	if (file[chr + 1] == '\0')
	{
		tmp = parsing_split(command->table[arg]->args[arg + 1], '>');
		file[i] = ft_strdup(tmp[0]);
	}
	else if (chr == 0)
	{
		tmp = parsing_split(command->table[arg]->args[arg], '>');
		file[i] = ft_strdup(tmp[0]);
	}
	else
	{
		tmp = parsing_split(command->table[arg]->args[arg], '>');
		file[i] = ft_strdup(tmp[1]);
	}
	file[i + 1] = NULL;
	return (free(tmp), 0);
}

int	assign_util_double_in(t_data *command, int arg, int table, int chr)
{
	int i;
	char **tmp;
	char **file;

	file = command->table[table]->double_in;
	i = 0;
	while (file[i])
		i++;
	if (file[chr + 1] == '\0')
	{
		tmp = parsing_split(command->table[arg]->args[arg + 1], '<');
		file[i] = ft_strdup(tmp[0]);
	}
	else if (chr == 0)
	{
		tmp = parsing_split(command->table[arg]->args[arg], '<');
		file[i] = ft_strdup(tmp[0]);
	}
	else
	{
		tmp = parsing_split(command->table[arg]->args[arg], '<');
		file[i] = ft_strdup(tmp[1]);
	}
	file[i + 1] = NULL;
	return (free(tmp), 0);
}

int	assign_util_double_out(t_data *command, int arg, int table, int chr)
{
	int i;
	char **tmp;
	char **file;

	file = command->table[table]->double_out;
	i = 0;
	while (file[i])
		i++;
	if (arg + 1 == '\0')
	{
		tmp = parsing_split(command->table[arg]->args[arg + 1], '>');
		file[i] = ft_strdup(tmp[0]);
	}
	else if (arg == 0)
	{
		tmp = parsing_split(command->table[arg]->args[arg], '>');
		file[i] = ft_strdup(tmp[0]);
	}
	else
	{
		tmp = parsing_split(command->table[arg]->args[arg], '>');
		file[i] = ft_strdup(tmp[1]);
	}
	file[i + 1] = NULL;
	return (free(tmp), 0);
}
