/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpedrosa <rpedrosa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 15:56:34 by rpedrosa          #+#    #+#             */
/*   Updated: 2025/02/24 16:34:32 by rpedrosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

static char	*expande(char *s, int j)
{
	char *temp;
	char *env;
	int	i;

	i = 0;
	temp = ft_strdup(s);
	s[j - 1] = '\0';
	temp += j;
	while (temp[i] && temp[i] != ' ' && temp[i] != '$' && \
		temp[i] != 34 && temp[i] != 39)
		i++;
	temp[i] = '\0';
	env = getenv(temp);
	temp += i + 1;
	s = ft_strjoin(s, env);
	s = ft_strjoin(s, temp);
	return (s);
}

static void	quote_found(int	*quote, int *single)
{
	if (*quote == 0 && *single == 0)
		*quote = 1;
	else if (*quote == 1)
		*quote = 0;
	if (*single == 0 && *quote == 0)
		*single = 1;
	else if (*single == 1)
		*single = 0;
}

void  handle_quote(char **s)
{
	int	i;
	int	j;
	int	quote;
	int	single;

	j = -1;
	i = -1;
	single = 0;
	quote = 0;
	while (s[++i])
	{
		while (s[i][++j])
		{
			if (s[i][j] == 34 || s[i][j] == 39)
				quote_found(&quote, &single);
			else if (s[i][j] == '$' && single == 0)
				s[i] = expande(s[i], j + 1);
		}
	}
}
