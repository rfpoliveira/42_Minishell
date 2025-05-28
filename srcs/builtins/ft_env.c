/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpatrici <jpatrici@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 14:07:19 by jpatrici          #+#    #+#             */
/*   Updated: 2025/05/28 16:54:06 by jpatrici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int	env_len(t_env *env)
{
	int	i;

	i = 0;
	while (env)
	{
		if (env->value)
			i++;
		env = env->next;
	}
	return (i);
}

int	ft_env(t_data *data)
{
	t_env *head;

	head = data->env;
	while (data->env)
	{
		if (data->env->value)
		{
			ft_putstr_fd(data->env->key, 1);
			ft_putstr_fd("=", 1);
			ft_putstr_fd(data->env->value, 1);
			ft_putstr_fd("\n", 1);
		}
		data->env = data->env->next;
	}
	data->env = head;
	return (0);
}

int	ft_unset(t_simple_command *cmd, t_data *data)
{
	int		i;
	t_env	*head;

	head = data->env;
	while (data->env)
	{
		i = 0;
		while (cmd->args[++i])
		{
			if (data->env->prev == NULL &&
				!ft_strncmp(cmd->args[i], data->env->key, ft_strlen(data->env->key)))
			{
				head = data->env->next;
				free(data->env->key);
				free(data->env->value);
				data->env = head;
				data->env->prev = NULL;
			}
			else if (data->env->next == NULL &&
				!ft_strncmp(cmd->args[i], data->env->key, ft_strlen(data->env->key)))
			{
				data->env->prev->next = NULL;
				data->env->prev = NULL;
				free(data->env->key);
				free(data->env->value);
			}
			else if (!ft_strncmp(cmd->args[i], data->env->key, ft_strlen(data->env->key)))
			{
				data->env->prev->next = data->env->next;
				data->env = data->env->prev;
				free(data->env->next->prev->key);
				free(data->env->next->prev->value);
				data->env->next->prev = data->env;
			}
		}
		data->env = data->env->next;
	}
	data->env = head;
	return (0);
}
