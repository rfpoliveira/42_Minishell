/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpatrici <jpatrici@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 19:09:31 by jpatrici          #+#    #+#             */
/*   Updated: 2025/05/15 19:09:33 by jpatrici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int	ft_echo(t_simple_command *cmd)
{
	int	i;

	i = 0;
	while (cmd->args[++i])
		ft_printf("%s", cmd->args[i]);
	if (!flagsearch(cmd))
		write(1, "\n", 1);
}
