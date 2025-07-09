/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpedrosa <rpedrosa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 19:33:53 by jpatrici          #+#    #+#             */
/*   Updated: 2025/07/08 19:09:41 by rpedrosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/exec.h"

char	*ft_strjoin_free(char *s1, char *join)
{
	char	*tmp;

	tmp = ft_strjoin(s1, join);
	if (s1)
		free(s1);
	return (tmp);
}

void	set_shlvl(t_env **env)
{
	t_env	*n;
	int		num;

	n = *env;
	while (n->next)
	{
		if (!ft_strncmp(n->key, "SHLVL", ft_strlen(n->key) + 1))
		{
			if (n->value)
			{
				num = ft_atoi(n->value) + 1;
				free(n->value);
				n->value = ft_itoa(num);
			}
			else
				n->value = ft_itoa(1);
			break ;
		}
		n = n->next;
	}
	if (ft_strncmp(n->key, "SHLVL", ft_strlen(n->key) + 1))
		env_addback(*env, env_new("SHLVL=1"));
}

int	check_cd(t_simple_command *cmd, t_data *data)
{
	if (cmd->number_args > 2)
		return (data->exit_code = -3, 1);
	return (0);
}

int	hd_counter(t_data *data)
{
	int	i;
	int	j;
	int	count;

	count = 0;
	i = -1;
	while (data->table[++i])
	{
		j = -1;
		while (data->table[i]->double_in[++j])
			count++;
	}
	return (count);
}

int	hd_iter(t_data *data)
{
	int	i;
	int	j;
	int	count;

	count = 0;
	i = -1;
	while (data->table[++i])
	{
		j = -1;
		while (data->table[i]->double_in[++j])
		{
			data->hd[count] = ft_heredoc(data->table[i]->double_in[j]);
			if (!data->hd[count++])
				return (0);
		}
	}
	return (1);
}
