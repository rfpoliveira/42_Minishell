/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_handle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpatrici <jpatrici@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 17:28:08 by jpatrici          #+#    #+#             */
/*   Updated: 2025/03/25 20:51:32 by jpatrici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/exec.h"
#include <stdlib.h>
#include <unistd.h>

int	pipe_child(t_simple_command *cmd, t_data *data, int *fd)
{
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	exec_cmd(cmd, data);
	return (1);
}

int	pipe_parent(t_data *data, int *fd)
{
	pid_t	pid;
	int status;

	close(fd[0]);
	pid = fork();
	if (pid == 0)
	{
		dup2(fd[1], STDOUT_FILENO);
		pipe_init(data);
		close(fd[1]);
		exit(0);
	}
	else
		close(fd[1]);
	waitpid(-1, &status, 0);
	return (1);
}

int	pipe_handle(t_data *data, int *fd)
{
	pid_t	pid;
	int		status;
	int		index;

	index = 0;
	if (data->number_simple_commands > 1)
	{
		pid = fork();
		if (pid == 0)
			pipe_child(*data->table, data, fd);
		else if (pid > 0)
		{
			data->table++;
			pipe_parent(data, fd);
		}
		else
			exit(data->exit_code);
	}
	else
		printf("%s\n", data->table[0]->args[0]);
	exec_cmd(data->table[0], data);
	waitpid(-1, &status, 0);
	data->exit_code = WIFEXITED(status);
	return (0);
}

int	pipe_init(t_data *data)
{
	int	fd[2];
	int	status;

	if(pipe(fd) == -1)
		return (0);
	else
		pipe_handle(data, fd);
	waitpid(-1, &status, 0);
	close(fd[0]);
	close(fd[1]);
	return (1);
}
