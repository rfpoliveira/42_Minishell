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

#include "../../incs/exec.h"

char **pathfind(char **envp)
{
	char	**path;
	int		j;

	j = 0;
	path = NULL;
	while (envp[++j])
		if (ft_strnstr(envp[j], "PATH=", 5))
			path = ft_split(&envp[j][5], ':');
	return (path);
}

int	setpaths(t_simple_command *cmd, char **paths)
{
	int		i;
	int		n;

	i= -1;
	n =  0 + (cmd->args[0][0] == '|');
	while (paths[++i])
	{
		cmd->paths = ft_strjoin(paths[i], "/");
		cmd->paths = ft_strjoin(cmd->paths, cmd->args[n]);
		if (access(cmd->paths, F_OK) != -1
			&& open(cmd->paths, O_DIRECTORY) == -1)
			break ;
		else
			free(cmd->paths);
	}
	return (1);
}
/**/
/*int	exec_pipe(t_simple_command *cmd, char **paths, char **envp)*/
/*{*/
/*	if (*cmd->args[0] == '|')*/
/*		cmd->args++;*/
/*	(void) paths;*/
/*	(void) envp;*/
/*	return (1);*/
/*}*/

int	exec_cmd(t_simple_command *cmd, t_data *data)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		setpaths(cmd, paths);
		execve(cmd->paths, cmd->args, env);
	}
	waitpid(pid, NULL, 0);
	return (0);
}

void	ft_cmd(t_command *cmd, char **envp)
{
	char	**paths;
	int		i;

	i = 0;
	paths = NULL;
	paths = pathfind(envp);
	exec_pipe(cmd->table,paths, envp);

	exec_cmd(cmd->table[i], paths, envp);
}
