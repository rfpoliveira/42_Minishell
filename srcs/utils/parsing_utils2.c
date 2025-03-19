/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renato-oliveira <renato-oliveira@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 12:03:29 by rpedrosa          #+#    #+#             */
/*   Updated: 2025/03/19 15:25:37 by renato-oliv      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"
#include "../../incs/parsing.h"

//counts the arguments present in the command passed
int	count_args(t_simple_command *simple)
{
	int	i;

	i = 0;
	while (simple->args[i])
		i++;
	return (i);
}
