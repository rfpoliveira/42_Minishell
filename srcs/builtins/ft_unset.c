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

char	*env_str(t_env *t)
{
	char	*s;

	s = NULL;
	s = ft_strdup(t->key);
	if (t->value)
	{
		s = ft_strjoin_free(s, "=");
		s = ft_strjoin_free(s, t->value);
	}
	return (s);
}

t_env	*unset_var(t_data *data, int index)
{
	char	**env;
	t_env	*t;
	t_env	*temp;
	int		i;

	t = data->env;
	env = ft_calloc(sizeof(char *), env_len(t) + 100);
	i = -1;
	while (t)
	{
		if (++i != index && t->key)
			env[i] = env_str(t);
		if (i == index)
		{
			i--;
			index = -1;
		}
		if (t)
			t = t->next;
	}
	init_envp(&temp, env);
	return (free_t_env(data->env), matrix_free(env), temp);
}

void	set_head(t_env **head, t_data *data, int n)
{
	int	j;

	*head = data->env;
	j = 0;
	while (*head && j < n)
	{
		*head = (*head)->next;
		j++;
	}
}

int	ft_unset(t_simple_command *cmd, t_data *data)
{
	int		i;
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
				set_head(&head, data, n);
			}
		}
		++n;
		if (head)
			head = head->next;
	}
	return (0);
}
