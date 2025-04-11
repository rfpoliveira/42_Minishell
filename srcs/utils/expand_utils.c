/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpedrosa <rpedrosa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 14:30:00 by rpedrosa          #+#    #+#             */
/*   Updated: 2025/04/11 15:31:31 by rpedrosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"
#include "../../incs/parsing.h"

int	expande_exit_code(char **s, int *exit_code)
{
	free(*s);
	*s = ft_itoa(*exit_code);
	if (*s == NULL)
		return (print_error(MALLOC_ERROR, exit_code), 1);
	return (0);
}
char	*get_prev(char *s, int x)
{
	char *prev;
	
	if (x != 1)
	{
		prev = ft_substr(s, 0, x - 1);
		if (!prev)
			return (NULL);
		prev[x - 1] = '\0';	
	}
	else
	{
		prev = ft_strdup("");
			if (!prev)
				return (NULL);
	}
	return (prev);
}

int my_get_env(char *s, char **env, int x)
{
	char *tmp;
	int	len;

	len = ft_strlen(s);
	if (s[len - 1] == 34)
		len--;
	len -= x;
	tmp = ft_substr(s, x, len);
	if (!tmp)
		return (MALLOC_ERROR);
	*env = getenv(tmp);
	return (free(tmp), 0);
}

int	get_str(char **s, char *prev, char *env, int len)
{
	if ((*s)[len - 2] == 34)
		len--;
	free(*s);
	*s = ft_calloc(len, sizeof(char));
	if (!(*s))
		return (MALLOC_ERROR);
	ft_strlcat(*s, prev, len);
	if (env)
		ft_strlcat(*s, env, len);
	return (0);
}
