/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tilde.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpedrosa <rpedrosa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 18:08:37 by rpedrosa          #+#    #+#             */
/*   Updated: 2025/07/08 21:00:29 by rpedrosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"
#include "../../incs/exec.h"

int	sum_everything(char *user, char *post, int i)
{
	int	sum;

	sum = ft_strlen(user) + ft_strlen(post) + 7;
	if (i == 2)
		sum++;
	return (sum);
}

int	join_arguments(char **arg, char *post, char *user, int i)
{
	int		sum_len;

	sum_len = sum_everything(user, post, i);
	(*arg) = ft_calloc(sum_len, 1);
	if ((*arg) == NULL)
		return (free(post), free(user), 1);
	ft_strlcat((*arg), "/home/", sum_len);
	ft_strlcat((*arg), user, sum_len);
	if (i == 2)
		ft_strlcat((*arg), "/", sum_len);
	ft_strlcat((*arg), post, sum_len);
	return (0);
}

int	ex_tilde(t_data *data, char **arg)
{
	int		i;
	char	*post;
	char	*user;

	i = 1;
	post = NULL;
	if ((*arg)[i] == '/')
		i++;
	post = ft_strdup(&(*arg)[i]);
	if (post == NULL)
		return (1);
	user = ft_find_value(data->env, "USER");
	if (user == NULL)
		user = ft_strdup("UNKNOWN_USER");
	ft_free(arg);
	if (join_arguments(arg, post, user, 2) != 0)
		return (1);
	return (free(post), free(user), 0);
}

int	handle_tilde(t_data *command)
{
	int	table;
	int	arg;

	table = -1;
	while (command->table[++table])
	{
		arg = -1;
		while (command->table[table]->args[++arg])
		{
			if (command->table[table]->args[arg][0] == '~' \
&& (command->table[table]->args[arg][1] == '/' \
|| command->table[table]->args[arg][1] == '\0'))
				return (ex_tilde(command, &command->table[table]->args[arg]));
		}
	}
	return (0);
}
