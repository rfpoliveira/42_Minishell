/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpedrosa <rpedrosa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 16:58:49 by jpatrici          #+#    #+#             */
/*   Updated: 2025/07/08 18:33:53 by rpedrosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/exec.h"

int	export_swap(t_env **exp)
{
	t_env	*p;
	t_env	*temp;

	temp = ft_calloc(sizeof(t_env), 1);
	p = (*exp);
	while ((*exp) && !is_sorted(*exp))
	{
		while ((*exp)->next)
		{
			if (ft_strncmp((*exp)->key, (*exp)->next->key,
					ft_strlen((*exp)->key)) > 0)
				swap_util(exp, temp);
			*exp = (*exp)->next;
		}
		*exp = p;
	}
	*exp = p;
	free(temp);
	return (0);
}

int	ft_print_export(t_env *env)
{
	if (!env)
		return (0);
	while (env)
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(env->key, 1);
		if (env->value)
		{
			ft_putstr_fd("=\"", 1);
			ft_putstr_fd(env->value, 1);
			ft_putstr_fd("\"\n", 1);
		}
		else
			ft_putstr_fd("\n", 1);
		env = env->next;
	}
	return (0);
}

void	check_infile(t_data *data, t_simple_command *cmd)
{
	int	i;

	i = -1;
	while (data->table[++i])
		if (data->table[i] == cmd && data->table[i + 1]
			&& data->table[i + 1]->infile)
			close(1);
}

void	keysep_check(t_simple_command *cmd, t_data *data, int keysep, int i)
{
	keysep = ft_strchrlen(cmd->args[i], '=');
	keysep = export_parse(cmd->args[i], keysep);
	if (keysep == 0)
	{
		data->exit_code = 1;
		export_error(cmd->args[i]);
		return ;
	}
	printf("%s\n", cmd->args[i]);
	ft_add_key(&data->env, cmd->args[i], keysep);
}

int	ft_export(t_simple_command *cmd, t_data *data)
{
	t_env	*temp;
	int		i;
	int		keysep;

	if (redirects(cmd, data, 1) == -1)
		return (1);
	temp = data->env;
	i = 0;
	keysep = 0;
	data->exit_code = 0;
	while (cmd->args[++i])
		keysep_check(cmd, data, keysep, i);
	export_swap(&data->env);
	check_infile(data, cmd);
	if (i == 1)
		ft_print_export(data->env);
	return (data->env = temp, 0);
}
