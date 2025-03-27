/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpatrici <jpatrici@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 19:38:20 by jpatrici          #+#    #+#             */
/*   Updated: 2025/03/27 21:11:41 by jpatrici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/exec.h"

t_env	*envp_cpy(char *envp)
{
	int		i;
	t_env	*env;

	env = ft_calloc(sizeof(t_env), 1);
	env->next = NULL;
	env->prev = NULL;
	env->var = ft_strdup(envp);
	return (env);
}

void	env_addback(t_env **env)
{
	t_env	*p;

	p = *env;
	if (!p)
	{

	}
}

void	init_data(t_data *data, t_command *cmd)
{
	data = ft_calloc(sizeof(t_data), 1);
	data->command = cmd;
	data->env = init_envp();
	data->paths = pathfind(env);
}
