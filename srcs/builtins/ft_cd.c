/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpedrosa <rpedrosa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 19:33:53 by jpatrici          #+#    #+#             */
/*   Updated: 2025/06/27 15:57:59 by rpedrosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"
#include "../../incs/exec.h"

int	ft_cd(t_data *data, t_simple_command *cmd)
{
	char	*old_pwd;
	char	*tmp;
	char	*dir;

	dir = getcwd(NULL, 0);
	if (!ft_strncmp(cmd->args[0], "pwd", 4))
	{
		ft_putstr_fd(dir, 1);
		return (write(1, "\n", 1));
	}
	if (cmd->number_args > 2)
		exit_bash(NULL, data, TOO_MANY_ARGS);
	if (!ft_strncmp(cmd->args[1], dir, ft_strlen(dir)))
		exit_bash(NULL, data, 0);
	old_pwd = ft_strjoin("OLDPWD=", dir);
	dir = ft_strjoin_free(dir, "/");
	dir = ft_strjoin_free(dir, cmd->args[1]);
	if (opendir(dir) != NULL)
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
		free(old_pwd);
		free(dir);
		ft_putstr_fd(" No such file or directory", 2);
		exit_bash(NULL, data, 1);
	}
	return (0);
}
