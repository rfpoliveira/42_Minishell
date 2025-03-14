/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command_utils2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renato-oliveira <renato-oliveira@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 16:19:55 by rpedrosa          #+#    #+#             */
/*   Updated: 2025/03/14 16:35:48 by renato-oliv      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/parsing.h"
#include "../../incs/minishell.h"

//VER
int	parse_exit(t_simple_command *s)
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
			print_error(SYNTAX_ERROR);
	}
	return (0);
}
