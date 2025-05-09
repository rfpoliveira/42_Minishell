/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command_utils2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpedrosa <rpedrosa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 16:19:55 by rpedrosa          #+#    #+#             */
/*   Updated: 2025/03/20 15:47:14 by rpedrosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"
#include "../../incs/parsing.h"

//VER
int	parse_exit(t_simple_command *s, int *exit_code)
{
	int	i;
	int	j;

	i = 1;
	j = -1;
	if (s->args[0][0] == '|')
		i++;
	while (s->args[i][++j])
	{
		if (!ft_isdigit(s->args[i][j]))
			print_error(SYNTAX_ERROR, exit_code);
	}
	return (0);
}
