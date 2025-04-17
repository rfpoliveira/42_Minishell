/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpedrosa <rpedrosa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 14:53:37 by rpedrosa          #+#    #+#             */
/*   Updated: 2025/04/11 16:26:52 by rpedrosa         ###   ########.fr       */
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
	while (file[++j])
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
		i = -1;
	}
	return (0);
}
static int	expande_red(t_simple_command *curr_table, int *exit_code)
{
	if (curr_table->infile)
	{
		if (expande_red_util(curr_table->infile, exit_code) != 0)
				return (1);
	}
	if (curr_table->outfile)
	{
		if (expande_red_util(curr_table->outfile, exit_code) != 0)
			return (1);
	}
	if (curr_table->double_in)
	{
		if (expande_red_util(curr_table->double_in, exit_code) != 0)
			return (1);
	}
	if (curr_table->double_out)
	{
		if (expande_red_util(curr_table->double_out, exit_code) != 0)
			return (1);
	}
	return (0);
}
//iterates to expand in all arguments, ignores: $$
static int	expand_args(t_simple_command *curr_table, int *exit_code)
{
	int	j;
	int	x;

	x = -1;
	j = -1;
	while (curr_table->args[++j])
	{
		while (curr_table->args[j][++x])
		{
			if (curr_table->args[j][x] == 39)
				x += skip_quotes(curr_table->args[j], x);
			if (curr_table->args[j][x] == '$')
			{
				if (curr_table->args[j][x + 1] == '$')
				{
					x++;
					continue ;
				}
				if (expande(&curr_table->args[j], x + 1, exit_code) != 0)
					return (1);
			}
		}
		x = -1;
	}
	return (0);
}

int  handle_expanding(t_data *command)
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
