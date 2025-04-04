/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpedrosa <rpedrosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 14:53:37 by rpedrosa          #+#    #+#             */
/*   Updated: 2025/04/04 16:29:46 by rpedrosa         ###   ########.fr       */
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
	int		len;

	if ((*s)[x] == '?')
		return (expande_exit_code(s, exit_code));
	prev = get_prev(*s, x);
	if (!prev)
		return (MALLOC_ERROR);
	if (my_get_env(*s, &env, x) != 0)
		return (MALLOC_ERROR);
	len = ft_strlen(prev) + ft_strlen(env) + 1;
	if (get_str(s, prev, env, len) != 0)
		return (MALLOC_ERROR);
	free(prev);
	return (0);
}
//next 2 functions takes care of expanding 
//on redirection files since is diferent in some cases
static int	expande_red_util(char **file, int *exit_code)
{
	int	i;
	int j;

	i = -1;
	j = -1;
	while (file[++j][i])
	{
		while (file[j][++i])
			{
				if (file[j][i] == 39)
					i += skip_quotes(file[j], i);
				if (file[j][i] == '$')
				{
					if (file[j][i + 1] == '$')
					{
						i++;
						continue ;
					}
					if (expande(&file[j], i + 1, exit_code) != 0)
						return (1);
					if (ft_strncmp(file[j], "", 1) == 0)
						return (print_error(SYNTAX_ERROR, exit_code), 1);
				}
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
