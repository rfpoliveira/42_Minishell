/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpatrici <jpatrici@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 16:58:49 by jpatrici          #+#    #+#             */
/*   Updated: 2025/05/20 19:33:40 by jpatrici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"
#include <stdio.h>

int		is_sorted(t_env (*exp))
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

int		export_swap(t_env **exp)
{
	t_env	*p;
	t_env	*temp;

	temp = ft_calloc(sizeof(t_env), 1);
	p = (*exp);
	while (!is_sorted(*exp))
	{
		while ((*exp)->next)
		{
			if (ft_strncmp((*exp)->key, (*exp)->next->key, ft_strlen((*exp)->key)) > 0)
			{
				temp->key = ft_strdup((*exp)->key);
				temp->value = ft_strdup((*exp)->value);
				free((*exp)->key);
				free((*exp)->value);
				(*exp)->key = ft_strdup((*exp)->next->key);
				(*exp)->value = ft_strdup((*exp)->next->value);
				free((*exp)->next->key);
				free((*exp)->next->value);
				(*exp)->next->key = ft_strdup(temp->key);
				(*exp)->next->value = ft_strdup(temp->value);
				free(temp->key);
				free(temp->value);
			}
			*exp = (*exp)->next;
		}
		*exp = p;
	}
	*exp = p;
	return (0);
}

int		ft_add_key(t_env **env, char *args, int keysep)
{
	int		i;
	t_env	*temp;

	i = -1;
	temp = *env;
	while (*env)
	{
		if (!ft_strncmp((*env)->key, args, keysep))
		{
			if (args[keysep - 1] == '+')
				(*env)->value = ft_strjoin((*env)->value, &args[keysep - 1]);
			else
				(*env)->value = &args[1];
			*env = (*env)->next;
		}
		else
		{
			*env = temp;
			env_addback(*env, env_new(args));
			break ;
		}
	}
	return (0);
}

int		ft_export(t_simple_command *cmd, t_data *data)
{
	t_env	*temp;
	int		i;
	int		j;
	int		keysep;

	temp = data->env;
	i = 0;
	while (cmd->args[++i])
	{
		j = -1;
		keysep = ft_strchrlen(cmd->args[i], '=');
		while (++j < keysep)
			if ((cmd->args[i][j] != '_' && !ft_isalnum(cmd->args[i][j]))
				|| ft_isdigit(cmd->args[i][0]) 
				|| (cmd->args[i][j] == '+' && j != keysep - 1))
				keysep = 0;
		if (keysep == 0)
			continue ;
		ft_add_key(&data->env, cmd->args[i], keysep);
	}
	export_swap(&data->env);
	while (data->env)
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(data->env->key, 1);
		ft_putstr_fd("=", 1);
		ft_putstr_fd(data->env->value, 1);
		ft_putstr_fd("\n", 1);
		data->env = data->env->next;
	}
	data->env = temp;
	return (0);
}
