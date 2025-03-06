/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command_utils2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpedrosa <rpedrosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 16:19:55 by rpedrosa          #+#    #+#             */
/*   Updated: 2025/03/06 14:01:43 by rpedrosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/parsing.h"
#include "../../incs/minishell.h"

int parse_exit(t_simple_command *s)
{
	if (s->number_args > 2)
		return (print_error(TOO_MANY_ARGS), 1);
	return (0);
}
