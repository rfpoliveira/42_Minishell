/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpedrosa <rpedrosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 16:34:59 by rpedrosa          #+#    #+#             */
/*   Updated: 2025/04/09 15:52:23 by rpedrosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"
#include "../../incs/parsing.h"

int	check_red_out(t_data *command, int chr, int table, int arg)
{
	char *current;

	current = command->table[table]->args[arg];
	if (current[arg + 1] == '<')
		return (assign_double_out(command, table, arg, chr));
	else
		return (assign_outfile(command, table, arg, chr));
}

int	check_red_in(t_data *command, int chr, int table, int arg)
{
	char *current;

	current = command->table[table]->args[arg];
	if (current[chr + 1] == '>')
		return (assign_double_in(command, table, arg, chr));
	else
		return (assign_infile(command, table, arg, chr));
}

int check_for_red(t_data *command, int table, int arg)
{
	int chr;
	char *current;

	chr = -1;
	current = command->table[table]->args[arg];
	while(current[++chr])
	{
		if (current[chr] == '<')
			return (check_red_in(command, chr, table, arg));
		else if (current[chr] == '>')
			return (check_red_out(command, chr, table, arg));
		else
			return (0);
	}
	
}

int	parse_redirect(t_data *command)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (command->table[i])
	{
		while (command->table[i]->args[j])
		{
			if (check_for_red(command, i, j) != 0)
				return (1);
			j++;
		}
		j = 0;
		i++;
	}
}