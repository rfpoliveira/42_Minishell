/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_file_assign.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpedrosa <rpedrosa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 15:07:30 by rpedrosa          #+#    #+#             */
/*   Updated: 2025/04/11 15:31:51 by rpedrosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"
#include "../../incs/parsing.h"

int	assign_util_infile(t_data *command, int arg, int table, int chr)
{
	int i;
	int j;
	char **tmp;
	char **file;

	file = command->table[table]->infile;
	i = 0;
	j = 0;
	while (file[i])
		i++;
	if (command->table[table]->args[arg][chr + 1] == '\0')
	{
		tmp = parsing_split(command->table[table]->args[arg + 1], '<');
		file[i] = ft_strdup(tmp[0]);
	}
	else if (chr == 0)
	{
		tmp = parsing_split(command->table[table]->args[arg], '<');
		file[i] = ft_strdup(tmp[0]);
	}
	else
	{
		tmp = parsing_split(command->table[table]->args[arg], '<');
		while (tmp[++j])
			file[i++] = ft_strdup(tmp[j]);
	}
	file[i + 1] = NULL;
	return (matrix_free(tmp), 0);
}

int	assign_util_outfile(t_data *command, int arg, int table, int chr)
{
	int i;
	int j;
	char **tmp;
	char **file;

	file = command->table[table]->outfile;
	i = 0;
	j = 0;
	while (file[i])
		i++;
	if (command->table[table]->args[arg][chr + 1] == '\0')
	{
		tmp = parsing_split(command->table[table]->args[arg + 1], '>');
		file[i] = ft_strdup(tmp[0]);
	}
	else if (chr == 0)
	{
		tmp = parsing_split(command->table[table]->args[arg], '>');
		file[i] = ft_strdup(tmp[0]);
	}
	else
	{
		tmp = parsing_split(command->table[table]->args[arg], '>');
		while (tmp[++j])
			file[i++] = ft_strdup(tmp[j]);
	}
/* 	file[i + 1] = NULL; */
	return (matrix_free(tmp), 0);
}

int	assign_util_double_in(t_data *command, int arg, int table, int chr)
{
	int i;
	int j;
	char **tmp;
	char **file;

	file = command->table[table]->double_in;
	i = 0;
	j = 0;
	while (file[i])
		i++;
	if (command->table[table]->args[arg][chr + 2] == '\0')
	{
		tmp = parsing_split(command->table[table]->args[arg + 1], '<');
		file[i] = ft_strdup(tmp[0]);
	}
	else if (chr == 0)
	{
		tmp = parsing_split(command->table[table]->args[arg], '<');
		file[i] = ft_strdup(tmp[0]);
	}
	else
	{
		tmp = parsing_split(command->table[table]->args[arg], '<');
		while (tmp[++j])
			file[i++] = ft_strdup(tmp[j]);
	}
	file[i + 1] = NULL;
	return (matrix_free(tmp), 0);
}

int	assign_util_double_out(t_data *command, int arg, int table, int chr)
{
	int i;
	int j;
	char **tmp;
	char **file;

	file = command->table[table]->double_out;
	i = 0;
	j = 0;
	while (file[i])
		i++;
	if (command->table[table]->args[arg][chr + 2] == '\0')
	{
		tmp = parsing_split(command->table[table]->args[arg + 1], '>');
		file[i] = ft_strdup(tmp[0]);
	}
	else if (chr == 0)
	{
		tmp = parsing_split(command->table[table]->args[arg], '>');
		file[i] = ft_strdup(tmp[0]);
	}
	else
	{
		tmp = parsing_split(command->table[table]->args[arg], '>');
		while (tmp[++j])
			file[i++] = ft_strdup(tmp[j]);
	}
	file[i + 1] = NULL;
	return (matrix_free(tmp), 0);
}
