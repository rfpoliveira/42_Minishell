/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpedrosa <rpedrosa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 16:24:28 by jpatrici          #+#    #+#             */
/*   Updated: 2025/07/08 18:33:44 by rpedrosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/exec.h"

int	exit_error(t_simple_command *cmd, t_data *data)
{
	data->exit_code = 2;
	if (ft_strchr(cmd->args[1], '-'))
		exit_bash(NULL, data, 156);
	else if (ft_strchr(cmd->args[1], '+'))
		exit_bash(NULL, data, 100);
	else
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(cmd->args[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		exit_bash(NULL, data, 2);
	}
	return (0);
}

int	ft_exit(t_simple_command *cmd, t_data *data)
{
	int	exit_status;

	if (redirects(cmd, data, 1) == -1)
		return (1);
	if (cmd->args[1] && !ft_isdigit(cmd->args[1][0]))
		exit_error(cmd, data);
	else if (cmd->args[1] && cmd->args[2])
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		return (data->exit_code = 1);
	}
	if (cmd->args[1])
	{
		exit_status = ft_atoi(cmd->args[1]);
		if (exit_status < 0 || exit_status > 255)
			exit_status = 42;
	}
	else
		exit_status = data->exit_code;
	if (data->number_simple_commands == 1)
		ft_putstr_fd("exit\n", 2);
	return (exit_bash(NULL, data, exit_status), 0);
}
