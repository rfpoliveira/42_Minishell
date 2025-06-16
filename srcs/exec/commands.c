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

int	builtin_exec(t_simple_command *cmd, t_data *data)
{
	if (cmd->args[0] && !ft_strncmp(cmd->args[0], "echo", 5))
		return (redirects(cmd, data), ft_echo(cmd), 1);
	if ((cmd->args[0] && !ft_strncmp(cmd->args[0], "cd", 3))
	|| (cmd->args[0] && !ft_strncmp(cmd->args[0], "pwd", 4)))
		return (redirects(cmd, data), ft_cd(data, cmd));
	if (cmd->args[0] && !ft_strncmp(cmd->args[0], "export", 7))
		return (redirects(cmd, data), ft_export(cmd, data), 1);
	if (cmd->args[0] && !ft_strncmp(cmd->args[0], "env", 4))
		return (redirects(cmd, data), ft_env(data), 1);
	if (cmd->args[0] && !ft_strncmp(cmd->args[0], "unset", 6))
		return (redirects(cmd, data), ft_unset(cmd, data), 1);
	if (cmd->args[0] && !ft_strncmp(cmd->args[0], "exit", 5))
		return (redirects(cmd, data), ft_exit(cmd, data), 1);
	return (0);
}

int	node_exec(t_simple_command *cmd, t_data *data)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		setpaths(cmd, data->paths);
		redirects(cmd, data);
		if (cmd->args[0] && !builtin_exec(cmd, data))
			execve(cmd->paths, cmd->args, data->envp);
		exit_bash(NULL, data);
	}
	waitpid(pid, &status, 0);
	return (0);
}

int	exec_cmd(t_simple_command *cmd, t_data *data, pid_t *pid)
{
	if (data->number_simple_commands == 1)
		node_exec(cmd, data);
	else if (data->number_simple_commands > 1) 
	{
		setpaths(cmd, data->paths);
		redirects(cmd, data);
		if (cmd->args[0] && !builtin_exec(cmd, data))
			execve(cmd->paths, cmd->args, data->envp);
		else
		{
			if (pid)
				free(pid);
			exit_bash(NULL, data);
		}
		/*free_envp(data);*/
		exit(1);
	}
	return (0);
}

int	ft_cmd(t_data *data)
{
	int		i;
	pid_t	*pid;

	data->table[0]->paths = NULL;
	data->envp = envp_cpy(data->env);
	if (data->number_simple_commands == 1
		&& builtin_exec(data->table[0], data))
		return (1);
	if (data->number_simple_commands == 1)
		return (exec_cmd(data->table[0], data, NULL), 0);
	i = -1;
	while (++i < data->number_simple_commands)
		if (pipe(data->table[i]->fd) == -1)
			exit(1);
	pid = ft_calloc(sizeof(pid_t), data->number_simple_commands);
	fd_handler(data, pid);
	free(pid);
	return (0);
}
