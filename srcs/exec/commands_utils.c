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
#include <stdio.h>

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
	env->value = ft_strdup(ft_strchr(envp, '=') + 1);
	return (env);
}

char	**envp_cpy(t_env *envp)
{
	char	**env;
	t_env	*t;
	int		i;

	i = 0;
	t = envp;
	while (t)
	{
		t = t->next;
		i++;
	}
	env = ft_calloc(sizeof(char *), i + 1);
	t = envp;
	i = -1;
	while (t)
	{
		env[++i] = ft_strdup(t->key);
		env[i] = ft_strjoin(env[i], "=");
		env[i] = ft_strjoin(env[i], t->value);
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
	p->next = node;
}

void 	init_envp(t_env **env, char **envp)
{
	t_env	*n;

	*env  = env_new(*envp);
	if (!*env)
		return ;
	n = *env;
	while (n && (*(++envp)))
	{
		env_addback(*env, env_new(*envp));
		n = n->next;
	}
}

void	init_data(t_data *data, char **envp)
{
	init_envp(&data->env, envp);
	data->paths = pathfind(data->env);
}
