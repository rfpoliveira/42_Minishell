/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpedrosa <rpedrosa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 14:07:19 by jpatrici          #+#    #+#             */
/*   Updated: 2025/07/08 18:33:36 by rpedrosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/exec.h"

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

int	ft_env(t_simple_command *cmd, t_data *data)
{
	t_env	*head;

	if (redirects(cmd, data, 1) == -1)
		return (1);
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
