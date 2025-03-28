/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpedrosa <rpedrosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 14:53:37 by rpedrosa          #+#    #+#             */
/*   Updated: 2025/03/27 15:04:26 by rpedrosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/parsing.h"
#include "../../incs/minishell.h"

//trully expandes variables and maintains 
//whatever can come first in the argument
static int	expande(char **s, int x, int *exit_code)
{
	char	*prev;
	char	*env;
	char	*temp;
	int		free_flag;

	free_flag = 0;
	prev = NULL;
	if ((*s)[x] == '?')
		return (expande_exit_code(s, exit_code));
	if (x > 1)
	{
		prev = ft_substr(*s, 0, x - 1);
		if (prev == NULL)
			return (print_error(MALLOC_ERROR, exit_code), 1);
	}
	if (my_getenv(s, &env, &x, &free_flag) != 0)
		return (print_error(MALLOC_ERROR, exit_code), ft_free(&prev), 1);
	temp = ft_strjoin(prev, env);
	if (temp == NULL)
		return (print_error(MALLOC_ERROR, exit_code), 1);
	if (!env || !prev)
		free_flag +=1;
	free(*s);
	*s = ft_strdup(temp);
	if (*s == NULL)
		return (print_error(MALLOC_ERROR, exit_code), 1);
	if (ft_strncmp(env, "", 1) == 0)
		free_flag += 20;
	free_expand(temp, prev, env, free_flag);
	return (0);
}
//next 2 functions takes care of expanding 
//on redirection files since is diferent in some cases
static int	expande_red_util(char *file, int *exit_code)
{
	int	i;

	i = -1;
	while (file[++i])
	{
		if (file[i] == 39)
			i += skip_quotes(file, i);
		if (file[i] == '$')
		{
			if (file[i + 1] == '$')
			{
				i++;
				continue ;
			}
			if (expande(&file, i + 1, exit_code) != 0)
				return (1);
			if (ft_strncmp(file, "", 1) == 0)
				return (print_error(SYNTAX_ERROR, exit_code), 1);
		}
	}
	return (0);
}
static int	expande_red(t_simple_command *s, int *exit_code)
{
	if (s->infile)
	{
		if (expande_red_util(s->infile, exit_code) != 0)
				return (1);
	}
	if (s->outfile)
	{
		if (expande_red_util(s->outfile, exit_code) != 0)
			return (1);
	}
	if (s->double_in)
	{
		if (expande_red_util(s->double_in, exit_code) != 0)
			return (1);
	}
	if (s->double_out)
	{
		if (expande_red_util(s->double_out, exit_code) != 0)
			return (1);
	}
	return (0);
}
//iterates to expand in all arguments, ignores: $$
static int	expand_args(t_simple_command *simple, int *exit_code)
{
	int	j;
	int	x;

	x = -1;
	j = -1;
	while (simple->args[++j])
	{
		while (simple->args[j][++x])
		{
			if (simple->args[j][x] == 39)
				x += skip_quotes(simple->args[j], x);
			if (simple->args[j][x] == '$')
			{
				if (simple->args[j][x + 1] == '$')
				{
					x++;
					continue ;
				}
				if (expande(&simple->args[j], x + 1, exit_code) != 0)
					return (1);
			}
		}
		x = -1;
	}
	return (0);
}

int  handle_expanding(t_command *command)
{
	int	i;

	i = -1;
	while (command->table[++i])
	{
		if (expande_red(command->table[i], &command->exit_code) != 0)
			return (1);
		if (expand_args(command->table[i], &command->exit_code) != 0)
			return (1);
	}
	return (0);
}
