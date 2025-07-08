/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpedrosa <rpedrosa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 18:28:57 by jpatrici          #+#    #+#             */
/*   Updated: 2025/07/08 19:26:27 by rpedrosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/exec.h"

void	free_t_env(t_env *env)
{
	t_env	*p;

	if (env)
	{
		while (env)
		{
			p = env->next;
			if (env->key)
				free(env->key);
			if (env->value)
				free(env->value);
			free(env);
			env = p;
		}
	}
}

t_env	*unset_var(t_data *data, int index)
{
	char	**env;
	t_env	*t;
	t_env	*temp;
	int		i;

	t = data->env;
	env = ft_calloc(sizeof(char *), env_len(t) + 1);
	i = -1;
	while (t)
	{
		if (++i != index && t->key)
		{
			env[i] = ft_strdup(t->key);
			if (t->value)
			{
				env[i] = ft_strjoin_free(env[i], "=");
				env[i] = ft_strjoin_free(env[i], t->value);
			}
		}
		if (i == index)
		{
			i--;
			index = -1;
		}
		if (t)
			t = t->next;
	}
	init_envp(&temp, env);
	free_t_env(data->env);
	matrix_free(env);
	return (temp);
}

int	ft_unset(t_simple_command *cmd, t_data *data)
{
	int		i;
	int		j;
	int		n;
	t_env	*head;

	if (redirects(cmd, data, 1) == -1)
		return (1);
	head = data->env;
	n = 0;
	while (head)
	{
		i = 0;
		while (cmd->args[++i])
		{
			if (!ft_strncmp(cmd->args[i], head->key,
			   ft_strlen(head->key) + 1))
			{
				data->env = unset_var(data, n);
				head = data->env;
				j = 0;
				while (head && j < n)
				{
					head = head->next;
					j++;
				}
			}
		}
		++n;
		if (head)
			head = head->next;
	}
	return (0);
}
