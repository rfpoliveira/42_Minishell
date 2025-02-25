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
	int	i;
	char  *temp;
	char  *temp2;
	char  *temp3;
	char *env;

	i = j;
	temp = ft_strdup(s);
	temp2 = ft_strdup(s);
	while (temp[i] != ' ' && temp[i] != 34 && temp[i] != 39 && temp[i] != '$' && temp[i])
		i++;
	temp3 = malloc(i - j + 1);
	ft_memcpy(temp3, temp + j, i - j);
	temp3[i - j] = '\0';
	env = getenv(temp3);
	ft_free(temp3);
	temp2[j - 1] = '\0';
	temp3 = ft_strjoin(temp2, env);
	free(temp2);
	temp2 = ft_strjoin(temp3, temp + i);
	ft_free(temp);
	ft_free(temp3);
	free(s);
	return (temp2);
}

static void	quote_found(int	*quote, int *single, char c)
{
	if (c == 34)
	{
		if (*quote == 0 && *single == 0)
			*quote = 1;
		else if (*quote == 1)
			quote = 0;
	}
	else
	{
		if (*single == 0 && *quote == 0)
			*single = 1;
		else if (*single == 1)
			*single = 0;
	}
}

int	quote_counter(char *s)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (!s)
		return (0);
	while(s[i])
	{
		if (s[i] == 34 || s[i] == 39)
			count++;
		i++;
	}
	return (count);
}

void  handle_expanding(char **s)
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
			if (quote_counter(s[i]) % 2 != 0)
				exiting_program(s, NULL, QUOTE_ERROR);
			if (s[i][j] == 34 || s[i][j] == 39)
				quote_found(&quote, &single, s[i][j]);
			else if (s[i][j] == '$' && single == 0)
				s[i] = expande(s[i], j + 1);
		}
		j = 0;
	}
}
