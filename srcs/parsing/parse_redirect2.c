/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirect2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpedrosa <rpedrosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 16:37:15 by rpedrosa          #+#    #+#             */
/*   Updated: 2025/03/06 17:08:02 by rpedrosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"
#include "../../incs/parsing.h"

static int	assign_redirect(t_simple_command *simple, char **red, int arg, int char)
{
		
}

static int redirect_hopper(t_simple_command *simple, int arg, int char)
{
	if (simple->args[arg][char] == '<')
	{
		if (simple->args[arg][char + 1] == '<')
			return (TODO);
		else if (simple->args[arg][char + 1] == '\0')
			return (TODO);
	}
	else if (simple->args[arg][char] == '>')
	{
		if (simple->args[arg][char + 1] == '>')
			return (TODO);
		else if (simple->args[arg][char + 1] == '\0')
			return (TODO);
	}
	return (0);
}

int	handle_redirect(t_command *command)
{
	int	i;
	int	j;
	int x;
	int	error;

	i = -1;
	j = 0;
	x = 0;
	error = 0;
	while (command->table[++i])
	{
		while (command->table[i]->args[j])
		{
			while (command->table[i]->args[j][x])
			{
				if (command->table->args[j][x] == '<' || command->table->args[j][x] == '>')
					error = redirect_hopper(command->table[i], j , x);
				x++;
			}
			j++;
		}
	}
	return (error);
}