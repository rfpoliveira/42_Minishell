/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_code_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpatrici <jpatrici@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 20:47:17 by jpatrici          #+#    #+#             */
/*   Updated: 2025/06/25 20:49:53 by jpatrici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void	dir_check(t_data *data, t_simple_command *cmd)
{
	DIR	*dir;

	if (cmd->args[0] && (cmd->args[0][0] == '.' && !access(cmd->args[0], F_OK)))
	{
		if (!access(cmd->args[0], F_OK | R_OK))
			ft_putstr_fd(" Is a directory\n", 2);
		else if (access(cmd->args[0], R_OK))
			ft_putstr_fd(" Permission denied", 2);
		exit_bash(NULL, data, 126);
	}
	if (cmd->args[0] && (cmd->args[0][0] == '.' \
	|| cmd->args[0][0] == '/') && ((dir = opendir(cmd->args[0])) != NULL))
	{
		if (access(cmd->args[0], R_OK))
			ft_putstr_fd(" Permission denied", 2);
		else
			ft_putstr_fd(" Is a directory\n", 2);
		exit_bash(NULL, data, 126);
	}
	if (cmd->args[0] && (cmd->args[0][0] == '.' || cmd->args[0][0] == '/') && access(cmd->args[0], F_OK)) 
		ft_putstr_fd(" No such file or directory\n", 2);
	else if (cmd->args[0])
		ft_putstr_fd(" command not found\n", 2);
	if (cmd->args[0])
		exit_bash(NULL, data, 127);
}
