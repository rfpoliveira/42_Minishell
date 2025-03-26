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
#include <unistd.h>

int	pipe_child(t_command *cmds, t_data *data, int *fd)
{
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	exec_cmd()
	return (1);
}

int	pipe_parent(t_command *cmds, t_data *data, int *fd)
{
	pid_t	pid;
	int status;

	close(fd[0]);
	pid = fork();
	if (pid == 0)
	{
		dup2(fd[1], STDOUT_FILENO);
		pipe_init(cmds, data);
		close(fd[1]);
		exit(0);
	}
	else
		close(fd[1]);
	waitpid(-1, &status, NULL);
	return (1);
}

int	pipe_handle(t_command *cmds, t_data *data, int *fd)
{
	pid_t	pid;

	if (cmds->number_simple_commands > 1)
	{
		pid = fork();
		if (pid == 0)
			pipe_child(cmds, data, fd);
		else if (pid > 0)
			pipe_parent(cmds, data, fd);
		else
			exit(127);
 
	}
}

int	pipe_init(t_command *cmds, t_data *data)
{
	int	fd[2];
	int	status;

	if(pipe(fd) == -1)
		return (0);
	else
		pipe_handle(cmds, data, fd);
	waitpid(-1, &status, 0);
	close(fd[0]);
	close(fd[1]);
	return (1);
}
