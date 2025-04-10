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

char **pathfind(t_env *envp)
{
	char	**path;
	t_env	*p;
	int		j;

	j = 0;
	path = NULL;
	p = envp;
	while (p->next)
	{
		if (ft_strnstr(p->var, "PATH=", 5))
			path = ft_split(&p->var[5], ':');
		p = p->next;
	}
		return (path);
}

int	setpaths(t_simple_command *cmd, char **paths)
{
	int		i;
	/*int		n;*/

	i= -1;
	if (cmd->paths)
		free(cmd->paths);
	else
		cmd->paths = NULL;
	/*n =  0 + (cmd->args[0][0] == '|');*/
	while (paths[++i])
	{
		cmd->paths = ft_strjoin(paths[i], "/");
		cmd->paths = ft_strjoin(cmd->paths, *cmd->args);
		if (access(cmd->paths, F_OK) != -1
			&& open(cmd->paths, O_DIRECTORY) == -1)
			break ;
		else
			free(cmd->paths);
	}
	return (1);
}

int	exec_cmd(t_simple_command *cmd, t_data *data)
{
	pid_t	pid;
	int		status;
	char	**temp;

	temp = envp_cpy(data->env);
	if (data->number_simple_commands == 1)
	{
		pid = fork();
		if (pid == 0)
		{
			setpaths(cmd, data->paths);
			execve(cmd->paths, cmd->args, temp);
			free(temp);
			exit(1);
		}
		waitpid(pid, &status, 0);
	}
	else 
	{
		setpaths(cmd, data->paths);
		/*dprintf(2, "%s\n", cmd->paths);*/
		execve(cmd->paths, cmd->args, temp);
		free(temp);
		exit(1);
	}	
	return (0);
}

void	ft_cmd(t_data *data)
{
	/*char	**paths;*/
	int		i;

	i = 0;
	data->table[0]->paths = NULL;
	/*exec_pipe((*data->command)->table[i]);*/
	/*printf("%s\n", (*data->command)->table[i]->args[0]);*/
	/*exec_cmd((*data->command)->table[i], data);*/
	pipe_init(data, -1);
}
