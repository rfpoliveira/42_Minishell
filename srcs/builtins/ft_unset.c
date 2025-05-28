#include "../../incs/minishell.h"

int unset_firstnode(t_data *data, t_env *head)
{
	head = data->env->next;
	free(data->env->key);
	free(data->env->value);
	data->env = head;
	data->env->prev = NULL;
    return (0);
}
int unset_lastnode(t_data *data)
{
    data->env->prev->next = NULL;
	data->env->prev = NULL;
	free(data->env->key);
	free(data->env->value);
    return (0);
}
int unset_middle(t_data *data)
{
	data->env->prev->next = data->env->next;
	data->env = data->env->prev;
	free(data->env->next->prev->key);
	free(data->env->next->prev->value);
	data->env->next->prev = data->env;
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
				!ft_strncmp(cmd->args[i], data->env->key, 
					ft_strlen(data->env->key)))
                unset_firstnode(data, head);
			else if (data->env->next == NULL &&
				!ft_strncmp(cmd->args[i], data->env->key, 
					ft_strlen(data->env->key)))
                unset_lastnode(data);
			else if (!ft_strncmp(cmd->args[i], data->env->key, 
				ft_strlen(data->env->key)))
                unset_middle(data);
		}
		data->env = data->env->next;
	}
	data->env = head;
	return (0);
}