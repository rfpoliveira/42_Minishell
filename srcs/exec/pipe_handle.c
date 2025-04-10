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

int	pipe_parent(t_data *data, int *fd, int index)
{
	pid_t	pidt;
	int status;

	close(fd[0]);
	pidt = fork();
	if (pidt == 0)
	{
		dup2(fd[1], STDOUT_FILENO);
		pipe_init(data, index);
		close(fd[1]);
		exit(0);
	}
	else
		close(fd[1]);
	waitpid(pidt, &status, 0);
	data->exit_code = WIFEXITED(status);
	return (1);
}

int	pipe_handle(t_data *data, int *fd, int index)
{
	pid_t	pid;
	/*int		status;*/

	printf("cmd num\t%d\n", data->number_simple_commands);
	if (data->number_simple_commands > 1 && data->table[index + 1])
	{
		pid = fork();
		if (pid == 0)
			pipe_child(data->table[index], data, fd);
		else if (pid > 0)
		{
			pipe_parent(data, fd, index);
		}
		else
			exit(data->exit_code);
	}
	else if (data->number_simple_commands == 1)
		exec_cmd(data->table[index], data);
	return (0);
}

int	pipe_init(t_data *data, int index)
{
	int	fd[2];
	int	status;

	/*dup2(fd[0], STDIN_FILENO);*/
	/*dup2(fd[1], STDOUT_FILENO);*/
	if(pipe(fd) == -1)
		return (0);
	else if (data->table[++index])
		pipe_handle(data, fd, index);
	waitpid(-1, &status, 0);
	data->exit_code = WEXITSTATUS(status);
	close(fd[0]);
	close(fd[1]);
	return (1);
}
