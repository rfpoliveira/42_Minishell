/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpatrici <jpatrici@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 19:13:09 by jpatrici          #+#    #+#             */
/*   Updated: 2025/05/16 19:13:48 by jpatrici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

char **pathfind(t_env *envp)
{
	char	**path;
	t_env	*p;

	path = NULL;
	p = envp;
	while (p->next)
	{
		if (ft_strnstr(p->key, "PATH", 5))
			path = ft_split(p->value, ':');
		p = p->next;
	}
		return (path);
}

int	setpaths(t_simple_command *cmd, char **paths)
{
	int		i;

	i= -1;
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

