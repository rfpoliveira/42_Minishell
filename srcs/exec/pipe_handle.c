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

#define READ 0
#define WRITE 1

int fd_handler(t_data *data)
{
	int pid[data->number_simple_commands - 1];
    int fd[data->number_simple_commands][2];
    int i;
	int j;
	int status;

	i = -1;
	j = -1;
	if (data->number_simple_commands == 1)
	{
		exec_cmd(data->table[0], data);
		return 0;
	}
    while (++i < data->number_simple_commands)
		if (pipe(fd[i]) == -1)
            exit (1);
	i = -1;
    while (++i < data->number_simple_commands)
	{
        pid[i] = fork();
        if (pid[i] == -1)
            exit (2);
        if (pid[i] == 0)
		{
            // Child process
		if (i < data->number_simple_commands - 1)
            {
				if (data->number_simple_commands == i +1)
				{
					exec_cmd(data->table[i], data);
					exit (0);
				}
				while (++j < data->number_simple_commands)
				{
	                if (i != j)
	                    close(fd[j][READ]);
	                if (i + 1 != j)
	                    close(fd[j][WRITE]);
	            }
				if (dup2(fd[i][READ], STDIN_FILENO) == -1)
				{
					printf("error on read\n");
					exit (1);		
				}
				if (dup2(fd[i + 1][WRITE], STDOUT_FILENO) == -1)
				{
					printf("error on write\n");
					exit (2);
				}
				close(fd[i][READ]);
		        close(fd[i + 1][WRITE]);
				exec_cmd(data->table[i], data);
				exit (2);

			}
        }
	}
	j = -1;
	while (++j < data->number_simple_commands)
	{
		if (j != 0)
			close(fd[j][WRITE]);
		if (j != data->number_simple_commands - 1)
			close(fd[j][READ]);
	}
	if (dup2(fd[0][WRITE], STDOUT_FILENO) == -1)
	{
		printf("error on write\n");
		exit (1);		
	}

	if (dup2(fd[data->number_simple_commands - 1][READ], STDIN_FILENO) == -1)
	{
		printf("error on read\n");
		exit (1);		
	}
    close(fd[0][WRITE]);
	/*close(fd[data->number_simple_commands][WRITE]);*/
	close(fd[data->number_simple_commands - 1][READ]);
	i = -1;
	while (++i < data->number_simple_commands - 1)
	/*	wait(NULL);*/
	/*(void) status;*/
	       waitpid(-1, &status, 0);
    return 0;
}
/**/
/*int	fd_handler(t_data *data)*/
/*{*/
/*	int		**fd;*/
/*	int		i;*/
/*	int		j;*/
/*	int		status;*/
/*	size_t	*pid;*/
/**/
/*	i = -1;*/
/*	j = -1;*/
/*	fd = NULL;*/
/*	if (data->number_simple_commands == 1)*/
/*	{*/
/*		exec_cmd(data->table[0], data);*/
/*	}*/
/*	fd = ft_calloc(sizeof(int *), data->number_simple_commands + 1);*/
/*	pid = ft_calloc(sizeof(pid_t), data->number_simple_commands);*/
/*	while (++i < data->number_simple_commands)*/
/*	{*/
/*		fd[i] = ft_calloc(sizeof(int), 2);*/
/*		if (pipe(fd[i]) == -1)*/
/*			exit (1);*/
/*	}*/
/*	i = 0;*/
/*	while (i++ < data->number_simple_commands - 1)*/
/*	{*/
/*		pid[i] = fork();*/
/*		if (!pid[i])*/
/*		{*/
/**/
/*				close(fd[i][1]);*/
/*				dup2(fd[i][0], 0);*/
/*				close(fd[i][0]);*/
/*				while (fd[++i])*/
/*				{*/
/*					close(fd[i][0]);*/
/*					close(fd[i][1]);*/
/*				}*/
/*			 while (++j < i - 1)*/
/*			{*/
/*				close(fd[j][0]);*/
/*				close(fd[j][1]);*/
/*			}*/
/*			close(fd[i][0]);*/
/*			dup2(fd[i - 1][0], 0);*/
/*			dup2(fd[i][1], 1);*/
/*			close(fd[i - 1][0]);*/
/*			close(fd[i][1]);*/
/*			exec_cmd(data->table[i], data);*/
/*		}*/
/*	}*/
/*	i = 0;*/
/*	while (pid[i++]) */
/*		waitpid(pid[i], &status, 0);*/
/*	return (0);*/
/*}*/
/*#include <stdio.h>*/
/*#include <stdlib.h>*/
/*#include <unistd.h>*/
/**/
/*int	pipe_child(t_simple_command *cmd, t_data *data, int *fd)*/
/*{*/
/*	if (index == (data->number_simple_commands - 1))*/
/*		dup2(fd[1], STDOUT_FILENO);*/
/*	close(fd[1]);*/
/*	dup2(fd[0], STDIN_FILENO);*/
/*	close(fd[0]);*/
/*	exec_cmd(cmd, data);*/
/*	return (1);*/
/*}*/
/**/
/*int	pipe_parent(t_data *data, int *fd, int index)*/
/*{*/
/*	pid_t	pidt;*/
/*	int status;*/
/**/
/*	pidt = fork();*/
/*	if (pidt == 0)*/
/*	{*/
/*		close(fd[0]);*/
/*		dup2(fd[1], STDOUT_FILENO);*/
/*		close(fd[1]);*/
/*		printf("here\n");*/
/*		pipe_init(data, index);*/
/*		exit(0);*/
/*	}*/
/*	else*/
/*	{*/
/*			close(fd[0]);*/
/*			close(fd[1]);*/
/*		close(fd[1]);*/
/*	}*/
/*	(void) index;*/
/*	waitpid(pidt, &status, 0);*/
/*	data->exit_code = WIFEXITED(status);*/
/*	return (1);*/
/*}*/
/**/
/*int	pipe_handle(t_data *data, int *fd, int index)*/
/*{*/
/*	pid_t	pid;*/
/*	int		status;*/
/**/
/*	printf("cmd num\t%d\n", data->number_simple_commands);*/
/*	if (data->number_simple_commands > 1 && data->table[index + 1])*/
/*	{*/
/*		pid = fork();*/
/*		if (pid == 0)*/
/*			pipe_child(data->table[index], data, fd);*/
/*		else if (pid > 0)*/
/*		{*/
/*			++index;*/
/*			pipe_parent(data, fd, index);*/
/*			close(fd[0]);*/
/*			close(fd[1]);*/
/*		}*/
/*			close(fd[0]);*/
/*			close(fd[1]);*/
/*		if (pid == -1)*/
/*			exit(data->exit_code);*/
/*	}*/
/*	if (data->number_simple_commands == 1)*/
/*		exec_cmd(data->table[index], data);*/
/*	printf("index\t%d\n", index);*/
/*	if (index + 1 == data->number_simple_commands)*/
/*	{*/
/**/
/*		printf("herefinally\n");*/
/*		exec_cmd(data->table[index], data);*/
/*	}*/
/*	return (0);*/
/*}*/
/**/
/*int	pipe_init(t_data *data, int index)*/
/*{*/
/*	int	fd[2];*/
/*	int	status;*/
/**/
/*	dup2(fd[0], STDIN_FILENO);*/
/*	dup2(fd[1], STDOUT_FILENO);*/
/*	printf("here\n");*/
/*	if(pipe(fd) == -1)*/
/*		return (0);*/
/*	else if (data->table[++index])*/
/*	{*/
/*		printf("here\n");*/
/*		pipe_handle(data, fd, index);*/
/*	}*/
/*	waitpid(-1, &status, 0);*/
/*	data->exit_code = WEXITSTATUS(status);*/
/*	close(fd[0]);*/
/*	close(fd[1]);*/
/*	return (1);*/
/*}*/
