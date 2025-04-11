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
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	pipe_child(t_simple_command *cmd, t_data *data, int *fd)
{
	/*if (index == (data->number_simple_commands - 1))*/
	/*	dup2(fd[1], STDOUT_FILENO);*/
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

	pidt = fork();
	if (pidt == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		printf("here\n");
		pipe_init(data, index);
		exit(0);
	}
	else
	{
			close(fd[0]);
			close(fd[1]);
		/*close(fd[1]);*/
	}
	(void) index;
	waitpid(pidt, &status, 0);
	data->exit_code = WIFEXITED(status);
	return (1);
}

int	pipe_handle(t_data *data, int *fd, int index)
{
	pid_t	pid;
	/*int		status;*/

	/*printf("cmd num\t%d\n", data->number_simple_commands);*/
	if (data->number_simple_commands > 1 && data->table[index + 1])
	{
		pid = fork();
		if (pid == 0)
			pipe_child(data->table[index], data, fd);
		else if (pid > 0)
		{
			++index;
			pipe_parent(data, fd, index);
			/*close(fd[0]);*/
			/*close(fd[1]);*/
		}
			close(fd[0]);
			close(fd[1]);
		if (pid == -1)
			exit(data->exit_code);
	}
	if (data->number_simple_commands == 1)
		exec_cmd(data->table[index], data);
	printf("index\t%d\n", index);
	if (index + 1 == data->number_simple_commands)
	{
		
		printf("herefinally\n");
		exec_cmd(data->table[index], data);
	}
	return (0);
}

int	pipe_init(t_data *data, int index)
{
	int	fd[2];
	int	status;

	/*dup2(fd[0], STDIN_FILENO);*/
	/*dup2(fd[1], STDOUT_FILENO);*/
	printf("here\n");
	if(pipe(fd) == -1)
		return (0);
	else if (data->table[++index])
	{
		printf("here\n");
		pipe_handle(data, fd, index);
	}
	waitpid(-1, &status, 0);
	data->exit_code = WEXITSTATUS(status);
	close(fd[0]);
	close(fd[1]);
	return (1);
}
