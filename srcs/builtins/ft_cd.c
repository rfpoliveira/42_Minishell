/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpedrosa <rpedrosa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 19:33:53 by jpatrici          #+#    #+#             */
/*   Updated: 2025/06/27 15:52:45 by rpedrosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"
#include "../../incs/exec.h"

int	ft_pwd(t_data *data, t_simple_command *cmd)
{
	char	*dir;

	dir = NULL;
	/*if (!dir || !dir[0] || !cmd->args[1])*/
	/*	return (0);*/
	if (!ft_strncmp(cmd->args[0], "pwd", 4))
	{
		dir = getcwd(NULL, 0);
		ft_putstr_fd(dir, 1);
		return (free(dir), write(1, "\n", 1));
	}
	if (cmd->number_args > 2)
		return (data->exit_code = -3, free(dir), 1);
	if (!ft_strncmp(cmd->args[1], dir, ft_strlen(dir)))
		return (free(dir), 1);
	return (free(dir), 0);
}

char	*ft_find_value(t_env *env, char *key)
{
	t_env	*head;
	char	*value;

	head = env;
	value = NULL;
	while (env)
	{
		if (!ft_strncmp(env->key, key, ft_strlen(env->key)))
			value = ft_strdup(env->value);
		env = env->next;
	}
	env = head;
	return (value);
}

char	*get_dir(t_data *data, t_simple_command *cmd, char **old_pwd)
{
	char	*dir;

	dir = NULL;
	if (!cmd->args[1])
	{
		dir = getcwd(NULL, 0);
		*old_pwd = ft_strjoin("OLDPWD=", dir);
		free(dir);
		dir = ft_find_value(data->env, "HOME");
		return (dir);
	}
	dir = getcwd(NULL, 0);
	*old_pwd = ft_strjoin("OLDPWD=", dir);
	dir = ft_strjoin_free(dir, "/");
	dir = ft_strjoin_free(dir, cmd->args[1]);
	return (dir);
}

int	ft_cd(t_data *data, t_simple_command *cmd)
{
	char	*old_pwd;
	char	*tmp;
	char	*dir;

	old_pwd = NULL;
	if (!ft_strncmp(cmd->args[0], "pwd", 4) && ft_pwd(data, cmd))
		return (1);
	dir = get_dir(data, cmd, &old_pwd);
	if (dir && open(dir, O_DIRECTORY) > 0)
	{
		ft_add_key(&data->env, old_pwd, 6);
		chdir(dir);
		free(dir);
		dir = getcwd(NULL, 0);
		tmp = ft_strjoin("PWD=", dir);
		ft_add_key(&data->env, tmp, 3);
		return (free(old_pwd), free(dir), free(tmp), 1);
	}
	else 
	{
		ft_putstr_fd(" No such file or directory\n", 2);
		return (free(old_pwd), free(dir), data->exit_code = 1);
	}
	return (0);
}
