/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpedrosa <rpedrosa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 19:38:20 by jpatrici          #+#    #+#             */
/*   Updated: 2025/06/27 15:02:05 by rpedrosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/exec.h"

t_env	*env_new(char *envp)
{
	t_env	*env;

	env = ft_calloc(sizeof(t_env), 1);
	if (!env)
		return (NULL);
	env->next = NULL;
	env->prev = NULL;
	if (envp[ft_strchrlen(envp, '=') - 1] == '+')
		env->key = ft_substr(envp, 0, ft_strchrlen(envp, '+'));
	else
		env->key = ft_substr(envp, 0, ft_strchrlen(envp, '='));
	if (!envp[ft_strchrlen(envp, '=')])
		env->value = NULL;
	else
		env->value = ft_strdup(ft_strchr(envp, '=') + 1);
	return (env);
}

char	**envp_cpy(t_env *envp)
{
	char	**env;
	t_env	*t;
	int		i;

	t = envp;
	env = ft_calloc(sizeof(char *), env_len(t) + 1);
	i = -1;
	while (t)
	{
		if (t->key && t->value)
		{
			env[++i] = ft_strdup(t->key);
			env[i] = ft_strjoin_free(env[i], "=");
			env[i] = ft_strjoin_free(env[i], t->value);
		}
		t = t->next;
	}
	env[++i] = NULL;
	return (env);
}

void	env_addback(t_env *env, t_env *node)
{
	t_env	*p;

	p = env;
	if (!p)
	{
		env = node;
		return ;
	}
	while (p->next)
		p = p->next;
	node->prev = p;
	p->next = node;
}

void	init_envp(t_env **env, char **envp)
{
	t_env	*n;

	*env = env_new(*envp);
	if (!*env)
		return ;
	n = *env;
	while (n && (*(++envp)))
	{
		env_addback(*env, env_new(*envp));
		n = n->next;
	}
	set_shlvl(env);
}

void	init_data(t_data *data, char **envp)
{
	data->paths = NULL;
	init_envp(&data->env, envp);
	data->paths = pathfind(data->env);
	data->hd = NULL;
	data->envp = NULL;
}
