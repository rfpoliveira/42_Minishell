/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpedrosa <rpedrosa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 14:30:00 by rpedrosa          #+#    #+#             */
/*   Updated: 2025/03/20 16:46:12 by rpedrosa         ###   ########.fr       */
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

//check if there is a even number of quotes
int	quote_counter(char **s, int *exit_code)
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
		return (print_error(QUOTE_ERROR, exit_code), 1);
}
//free temporary variables inside the expande function
//prev can always be freed (if NULL the functions does nothing)
//temp is only freed if env or prev are not null, if one of them are ft_strjoin does not allocate
//if getenv returns NULL we allocate "" and that must be freed
void	free_expand(char *temp, char *prev, char *env, int flag)
{
	ft_free(&prev);
	if (flag % 10 == 0)
		ft_free(&temp);
	if (flag >= 20 && *env != *temp)
		free(env);
}

static int  my_getenv_util(char **s, int *x, int *i, char **env, int *free_flag)
{
	char *buff;
	
	buff = NULL;
	buff = ft_substr(*s, *x, *i - *x - 1);
	if (buff == NULL)
		return (MALLOC_ERROR);
	*env = getenv(buff);
	ft_free(&buff);
	buff = ft_substr(*s, *i - 1, ft_strlen(*s) - *i);
	if (buff == NULL)
		return (MALLOC_ERROR);
	*env = ft_strjoin(*env, buff);
	if (*env == NULL)
		return (ft_free(&buff), MALLOC_ERROR);
	ft_free(&buff);
	*free_flag += 20;
	return (0);
}
//uses getenv in the correct string depending of the case
int	my_getenv(char **s, char **env, int *x, int *free_flag)
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
		{
			if (my_getenv_util(s, x, &i, env, free_flag) != 0)
				return (MALLOC_ERROR);
		}
	}
	else
	{
		*env = ft_substr(*s, *x + 1, ft_strlen(*s) - *x);
		if (*env == NULL)
			return (MALLOC_ERROR);
		*free_flag += 20;
	}
	if (*env == NULL)
	{
		*env = ft_strdup("");
		if (*env == NULL)
			return (MALLOC_ERROR);
		*free_flag += 20;
	}
	return (0);
}
