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

#define READ 0
#define WRITE 1

void	first_arg(t_data *data)
{
	int	j;

	j = -1;
	while (++j < data->number_simple_commands)
	{
		if (j != 0)
			close(data->table[j]->fd[READ]);
		if (j != 1)
			close(data->table[j]->fd[WRITE]);
	}
	close(data->table[0]->fd[READ]);
	dup2(data->table[1]->fd[WRITE], STDOUT_FILENO);
	close(data->table[1]->fd[WRITE]);
}

void	mid_args(t_data *data, int i)
{
	int	j;

	j = -1;
	while (++j < data->number_simple_commands)
	{
		if (j != i)
			close(data->table[j]->fd[READ]);
		if (j != i + 1)
			close(data->table[j]->fd[WRITE]);
	}
	dup2(data->table[i]->fd[READ], STDIN_FILENO);
	close(data->table[i]->fd[READ]);
	dup2(data->table[i + 1]->fd[WRITE], STDOUT_FILENO);
	close(data->table[i + 1]->fd[WRITE]);
}
void	last_arg(t_data *data, int i)
{
	int	j;

	j = -1;
	while (++j < data->number_simple_commands)
	{
		if (j != i)
		{
			close(data->table[j]->fd[READ]);
			close(data->table[j]->fd[WRITE]);
		}
	}
	dup2(data->table[i]->fd[READ], STDIN_FILENO);
	close(data->table[i]->fd[READ]);
	close(data->table[i]->fd[WRITE]);
}

void parent_process(t_data *data, pid_t *pid)
{
	int i;
	int status;

	i = -1;
	while (++i < data->number_simple_commands)
	{
		close(data->table[i]->fd[READ]);
		close(data->table[i]->fd[WRITE]);
	}
	i = -1;
	while (++i < data->number_simple_commands)
	   waitpid(pid[i], &status, 0);
	data->exit_code = WEXITSTATUS(status);
}

void fd_handler(t_data *data, pid_t *pid)
{
    int i;

	i = -1;
    while (++i < data->number_simple_commands)
	{
        pid[i] = fork();
        if (pid[i] == -1)
            exit (2);
		if (pid[i] == 0)
		{
			if (i == 0)
				first_arg(data);
			else if (i == data->number_simple_commands - 1)
				last_arg(data, i);
			else
				mid_args(data, i);
			exec_cmd(data->table[i], data, pid);
			dprintf(2, "exit on pipe:\t%d\n", data->exit_code);
			exit_bash(NULL, data, data->exit_code);
        }
	}
	parent_process(data, pid);
}
