/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpedrosa <rpedrosa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 18:07:39 by jpatrici          #+#    #+#             */
/*   Updated: 2025/06/27 15:52:33 by rpedrosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/exec.h"

int	builtin_exec(t_simple_command *cmd, t_data *data)
{
	if (cmd->args[0] && !ft_strncmp(cmd->args[0], "echo", 5))
		return (redirects(cmd, data),
			data->exit_code = ft_echo(cmd));
	if ((cmd->args[0] && !ft_strncmp(cmd->args[0], "cd", 3))
		|| (cmd->args[0] && !ft_strncmp(cmd->args[0], "pwd", 4)))
		return (redirects(cmd, data),
			data->exit_code = ft_cd(data, cmd));
	if (cmd->args[0] && !ft_strncmp(cmd->args[0], "export", 7))
		return (redirects(cmd, data),
			ft_export(cmd, data), 0);
	if (cmd->args[0] && !ft_strncmp(cmd->args[0], "env", 4))
		return (redirects(cmd, data),
			data->exit_code = ft_env(data));
	if (cmd->args[0] && !ft_strncmp(cmd->args[0], "unset", 6))
		return (redirects(cmd, data),
			data->exit_code = ft_unset(cmd, data));
	if (cmd->args[0] && !ft_strncmp(cmd->args[0], "exit", 5))
		return (redirects(cmd, data),
			data->exit_code = ft_exit(cmd, data));
	return (-1);
}

int	node_exec(t_simple_command *cmd, t_data **data)
{
	pid_t	pid;
	int		status;
	int		is_builtin;

	status = 0;
	pid = fork();
	if (pid == 0)
	{
		redirects(cmd, *data);
		setpaths(cmd, (*data)->paths);
		is_builtin = builtin_exec(cmd, *data);
		if (cmd->args[0] && is_builtin == -1)
			execve(cmd->paths, cmd->args, (*data)->envp);
		if (is_builtin == -1)
			dir_check(*data, cmd);
	}
	waitpid(pid, &status, 0);
	(*data)->exit_code = WEXITSTATUS(status);
	return (0);
}

int	exec_cmd(t_simple_command *cmd, t_data *data, pid_t *pid)
{
	int		is_builtin;

	if (data->number_simple_commands == 1)
		node_exec(cmd, &data);
	else if (data->number_simple_commands > 1)
	{
		if (pid)
			free(pid);
		redirects(cmd, data);
		setpaths(cmd, data->paths);
		is_builtin = builtin_exec(cmd, data);
		if (cmd->args[0] && is_builtin == -1)
			execve(cmd->paths, cmd->args, data->envp);
		if (is_builtin == -1)
		{
			ft_putstr_fd(" command not found\n", 2);
			exit_bash(NULL, data, 127);
		}
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
		&& builtin_exec(data->table[0], data) != -1)
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
