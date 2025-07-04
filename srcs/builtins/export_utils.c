/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpatrici <jpatrici@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 12:31:44 by jpatrici          #+#    #+#             */
/*   Updated: 2025/05/28 13:05:48 by jpatrici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int	swap_util(t_env **exp, t_env *temp)
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
	return (0);
}

int	export_parse(char *args, int keysep)
{
	int	i;

	i = -1;
	if ((args[keysep] == '\0' && keysep == 0)
		|| (args[keysep] == '\0' && args[keysep - 1] == '+'))
		return (0);
	while (++i < keysep)
	{
		if (args[i] == '+' && i == keysep - 1)
			break ;
		if ((args[i] != '_' && !ft_isalnum(args[i]))
			|| ft_isdigit(args[0]))
			keysep = 0;
	}
	return (keysep);
}

int	ft_add_key(t_env **env, char *args, int keysep)
{
	t_env	*head;

	head = *env;
	while (*env)
	{
		if (args[keysep] == '\0' && !ft_strncmp((*env)->key, args, keysep))
			return (0);
		keysep -= (args[keysep - 1] == '+');
		if (!ft_strncmp((*env)->key, args, keysep)
			&& (*env)->key[keysep] == '\0')
		{
			add_to_export(env, args, keysep);
			return ((*env = head), 0);
		}
		*env = (*env)->next;
	}
	*env = head;
	env_addback(*env, env_new(args));
	return (0);
}

int	export_error(char *error)
{
	ft_putstr_fd("bash: export: '", 2);
	ft_putstr_fd(error, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	return (0);
}

int	add_to_export(t_env **env, char *args, int keysep)
{
	char	*temp;

	temp = NULL;
	if (args[keysep] == '+')
	{
		temp = (*env)->value;
		(*env)->value = ft_strjoin(temp, &args[keysep + 2]);
		free(temp);
	}
	else if ((*env)->value || args[keysep] == '=' || args[keysep] == '+')
	{
		free((*env)->value);
		(*env)->value = ft_strdup(&args[keysep + 1]);
	}
	return (0);
}
