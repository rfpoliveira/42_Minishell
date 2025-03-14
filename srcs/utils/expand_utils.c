/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renato-oliveira <renato-oliveira@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 14:30:00 by rpedrosa          #+#    #+#             */
/*   Updated: 2025/03/14 09:56:30 by renato-oliv      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"
#include "../../incs/parsing.h"

int	quote_counter(char **s)
{
	int	i;
	int j;
	int	count;

	i = -1;
	j = -1;
	count = 0;
	if (!s)
		return (0);
	while (s[++j])
	{
		while(s[j][++i])
		{
			if (s[j][i] == 34 || s[j][i] == 39)
				count++;
		}
	}
	if (count % 2 == 0)
		return (0);
	else
		return (print_error(QUOTE_ERROR), 1);
}

void free_expand(char **temp, char **prev, char **env, int flag)
{
	if (flag == 1 || flag == 2)
	{
		free(*temp);
		free(*prev);
	}
	if (flag == 2)
		free(*env);
}

void	my_getenv(char **s, char **env, int *x, int *free_flag)
{
	if ((*s)[*x] != '$' && !ft_isdigit((*s)[*x]) && (*s)[*x] != '?')
		*env = getenv(*s + *x);
	else
	{
		*env = ft_substr(*s, *x + 1, ft_strlen(*s) - *x);
		*free_flag = 2;
	}
	if (*env == NULL)
	{
		*env = ft_strdup("");
		*free_flag = 2;
	}
}