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
	if (!path)
		return (ft_printf("ERROR\nPATH not found\n"), NULL);
	return (path);
}

int	setpaths(t_simple_command *cmd, char **paths)
{
	int		i;
	int		n;
	/*char	*temp;*/

	i= -1;
	n = 0;
	cmd->paths = ft_calloc(sizeof(char *), cmd->number_args + 1);
	if (!cmd->paths)
		return (0);
	while (paths[++i])
	{
		cmd->paths[n] = ft_strjoin(paths[i], "/");
		cmd->paths[n] = ft_strjoin(cmd->paths[n], cmd->args[n]);
		if (access(cmd->paths[n], F_OK) != -1
			&& open(cmd->paths[n], O_DIRECTORY) == -1
			&& n++)
			break ;
		else
			free(cmd->paths[n]);
	}
	return (1);
}

int	exec(t_simple_command *cmd, char **envp, int index)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
		execve(cmd->paths[index], cmd->args, envp);
	waitpid(pid, NULL, 0);
	return (0);
}

void	ft_cmd(t_simple_command *cmd, char **envp)
{
	char	**paths;

	paths = NULL;
	paths = pathfind(envp);
	if (!paths)
		exit(127);
	if (!setpaths(cmd, paths))
		exit(127);
	exec(cmd, envp, 0);
}

