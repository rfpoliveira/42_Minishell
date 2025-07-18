/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_envp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpatrici <jpatrici@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 16:34:02 by jpatrici          #+#    #+#             */
/*   Updated: 2025/06/05 17:30:22 by jpatrici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/exec.h"

void	free_cmd(t_data *data)
{
	int	i;

	i = -1;
	while (data->table[++i])
		if (data->table[i]->paths)
			free(data->table[i]->paths);
}

void	free_arrenvp(t_data *data)
{
	int	i;

	i = -1;
	if (data->envp)
	{
		while (data->envp[++i])
		{
			free(data->envp[i]);
			data->envp[i] = NULL;
		}
		free(data->envp);
		data->envp = NULL;
	}
}

void	free_env(t_data *data)
{
	t_env	*p;

	if (data->env)
	{
		while (data->env)
		{
			p = data->env->next;
			if (data->env->key)
				free(data->env->key);
			if (data->env->value)
				free(data->env->value);
			free(data->env);
			data->env = p;
		}
	}
}

void	free_hd(t_data *data)
{
	int	i;

	i = -1;
	if (data->hd)
	{
		while (data->hd[++i])
			free(data->hd[i]);
		free(data->hd);
	}
}

void	free_envp(t_data *data)
{
	int		i;

	free_arrenvp(data);
	free_env(data);
	i = -1;
	if (data->paths)
	{
		while (data->paths[++i])
			free(data->paths[i]);
		free(data->paths);
		data->paths = NULL;
	}
	if (data->table && *data->table)
		free_cmd(data);
	if (data->table && *data->table)
		while (data->table[++i])
			table_free(data->table);
	free_hd(data);
	free(data);
}
