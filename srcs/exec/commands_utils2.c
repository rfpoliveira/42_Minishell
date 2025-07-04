/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpedrosa <rpedrosa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 19:13:09 by jpatrici          #+#    #+#             */
/*   Updated: 2025/06/27 15:02:17 by rpedrosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/exec.h"

char	**pathfind(t_env *envp)
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

	i = -1;
	cmd->paths = NULL;
	if (cmd->args && *cmd->args)
	{
		while (paths[++i])
		{
			cmd->paths = ft_strjoin(paths[i], "/");
			cmd->paths = ft_strjoin_free(cmd->paths, *cmd->args);
			if (access(cmd->paths, F_OK) != -1
				&& open(cmd->paths, O_DIRECTORY) == -1)
				break ;
			else
			{
				free(cmd->paths);
				cmd->paths = NULL;
			}
		}
		if (!cmd->paths && *cmd->args)
			cmd->paths = ft_strdup(*cmd->args);
	}
	return (1);
}

int	is_sorted(t_env (*exp))
{
	t_env	*temp;

	temp = exp;
	while (temp->next)
	{
		if (ft_strncmp(temp->key, temp->next->key, ft_strlen(temp->key)) > 0)
			return (0);
		temp = temp->next;
	}
	return (1);
}

int	ft_strchrlen(char *s, char c)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != c && s[i] != '\0')
		i++;
	return (i);
}
