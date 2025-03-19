/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renato-oliveira <renato-oliveira@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 14:30:00 by rpedrosa          #+#    #+#             */
/*   Updated: 2025/03/19 15:25:25 by renato-oliv      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"
#include "../../incs/parsing.h"

//check if there is a even number of quotes
int	quote_counter(char **s)
{
	int	i;
	int	j;
	int	count;

	i = -1;
	j = -1;
	count = 0;
	if (!s)
		return (0);
	while (s[++j])
	{
		while (s[j][++i])
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
//free temporary variables inside the expande function
void	free_expand(char **temp, char **prev, char **env, int flag)
{
	ft_free(prev);
	ft_free(temp);
	if (flag == 2 && *env != *temp)
		free(*env);
}

static void  my_getenv_util(char **s, int *x, int *i, char **env, int *free_flag)
{
	char *buff;
	
	buff = NULL;
	buff = ft_substr(*s, *x, *i - *x - 1);
	*env = getenv(buff);
	ft_free(&buff);
	buff = ft_substr(*s, *i - 1, ft_strlen(*s) - *i);
	*env = ft_strjoin(*env, buff);
	ft_free(&buff);
	*free_flag = 2;

}
//uses getenv in the correct string depending of the case
void	my_getenv(char **s, char **env, int *x, int *free_flag)
{
	int	i;

	i = *x;
	while ((*s)[i] && !ft_isspace((*s)[i - 1]))
		i++;
	if ((*s)[*x] != '$' && !ft_isdigit((*s)[*x]) && (*s)[*x] != '?')
	{
		if (i == ft_strlen(*s) && (*s)[i - 1] != 34)
			*env = getenv(*s + *x);
		else
			my_getenv_util(s, x, &i, env, free_flag);
	}
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
