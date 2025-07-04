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

int	flagsearch(char *flag)
{
	int	i;

	i = 0;
	if (!flag || flag[0] != '-')
		return (0);
	while (flag[++i])
	{
		if (flag[0] == '-' && flag[i] == 'n')
			continue ;
		else
			return (0);
	}
	return (1);
}

int	ft_echo(t_simple_command *cmd)
{
	int	i;

	i = 0;
	while (flagsearch(cmd->args[i + 1]))
		i++;
	while (cmd->args[++i])
	{
		ft_putstr_fd(cmd->args[i], 1);
		if (cmd->args[i + 1])
			write(1, " ", 1);
	}
	if (!flagsearch(cmd->args[1]))
		write(1, "\n", 1);
	return (0);
}
