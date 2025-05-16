/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpatrici <jpatrici@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 18:07:39 by jpatrici          #+#    #+#             */
/*   Updated: 2025/03/17 18:07:47 by jpatrici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int	builtin_exec(t_simple_command *cmd)
{
	if (cmd->args[0] && !ft_strncmp(cmd->args[0], "echo", 5))
		return (ft_echo(cmd), 1);
	return (0);
}

int	node_exec(t_simple_command *cmd, t_data *data)
{
	pid_t	pid;
	int		status;
	char	**temp;

	temp = envp_cpy(data->env);
	pid = fork();
	if (pid == 0)
	{
		setpaths(cmd, data->paths);
		redirects(cmd);
		if (builtin_exec(cmd))
			exit(1);
		else
			execve(cmd->paths, cmd->args, temp);
		free(temp);
		exit(1);
	}
	waitpid(pid, &status, 0);
	return (0);
}

int	exec_cmd(t_simple_command *cmd, t_data *data)
{
	char	**temp;

	temp = envp_cpy(data->env);
	if (data->number_simple_commands == 1)
		node_exec(cmd, data);
	else if (data->number_simple_commands > 1) 
	{
		setpaths(cmd, data->paths);
		redirects(cmd);
		if (!builtin_exec(cmd))
			execve(cmd->paths, cmd->args, temp);
		else
			exit(-1);
		free(temp);
		exit(1);
	}
	return (0);
}

int	ft_cmd(t_data *data)
{
	int		i;
	pid_t	*pid;

	data->table[0]->paths = NULL;
	if (data->number_simple_commands == 1)
		return (exec_cmd(data->table[0], data), 0);
	i = -1;
	while (++i < data->number_simple_commands)
		if (pipe(data->table[i]->fd) == -1)
			exit(1);
	pid = ft_calloc(sizeof(pid_t), data->number_simple_commands);
	fd_handler(data, pid);
	free(pid);
	return (0);
}
