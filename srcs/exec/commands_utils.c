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

t_env	*env_new(char *envp)
{
	t_env	*env;

	env = ft_calloc(sizeof(t_env), 1);
	if (!env)
		return (NULL);
	env->next = NULL;
	env->prev = NULL;
	env->var = ft_strdup(envp);
	return (env);
}

char	**envp_cpy(t_env *envp)
{
	char	**env;
	t_env	*t;
	int		i;

	i = 0;
	t = envp;
	while (t){
		t = t->next;
		i++;
	}
	env = ft_calloc(sizeof(char *), i + 1);
	t = envp;
	i = -1;
	while (t)
	{
		env[++i] = ft_strdup(t->var);
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
	/*int i = -1;*/
	/*data = ft_calloc(sizeof(t_data), 1);*/
	/*(*data)->command = cmd;*/
	/*printf("%s\n", data->table[0]->args[0]);*/
	init_envp(&data->env, envp);
	/*data->table[0]->paths*/
	/*printf("DATA\t%d:\t%s\n", i, data->env->var);*/
	/*char **cpy = envp_cpy(data->env);*/
	data->paths = pathfind(data->env);
	/*while (envp[++i])*/
	/*{*/
	/*	printf("ENVP\t%d:\t%s\n", i, envp[i]);*/
	/*	printf("DATA\t%d:\t%s\n", i, data->env->var);*/
	/*printf("COPY\t%d:\t%s\n", i, cpy[i]);*/
	/*	data->env = data->env->next;*/
	/*}*/
}
