/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpedrosa <rpedrosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 16:34:59 by rpedrosa          #+#    #+#             */
/*   Updated: 2025/04/07 12:44:00 by rpedrosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"
#include "../../incs/parsing.h"

int	check_red_out(t_command *command, char *current, int arg, int table)
{
	if (current[arg + 1] == '<')
		return (assign_double_out(command,current, arg, table));
	else
		return (assign_outfile(command, current, arg, table));
}

int	check_red_in(t_command *command, char *current, int arg, int table)
{
	if (current[arg + 1] == '>')
		return (assign_double_in(command,current, arg, table));
	else
		return (assign_infile(command, current, arg, table));
}

int check_for_red(t_command *command, char *current, int table)
{
	int arg;

	while(current[arg])
	{
		if (current[arg] == '<')
			return (check_red_in(command, current, arg, table));
		else if (current[arg] == '>')
			return (check_red_out(command, current, arg, table));
		else
			return (0);
	}
	
}

int	parse_redirect(t_command *command)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (command->table[i])
	{
		while (command->table[i]->args[j])
		{
			if (check_for_red(command, command->table[i]->args[j], i) != 0)
				return (1);
			j++;
		}
		i++;
	}
}