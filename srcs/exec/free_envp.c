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

#include "../../incs/minishell.h"
/**/
/*void	free_cmd(t_simple_command * cmd)*/
/*{*/
/*	int	i;*/
/**/
/*	if (cmd->fd[0] && cmd->fd[1])*/
/*		free(cmd->fd);*/
/*	if ()*/
/*}*/
/**/
void	free_envp(t_data *data)
{
	int	i;
	t_env	*p;

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
		matrix_free(data->paths);
	}
	free(data);
	/*i = -1;*/
	/*while (data->table[++i])*/
	/*	free_cmd(data->table[i]);*/
	/*free(data);*/
}
