/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpedrosa <rpedrosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 15:56:34 by rpedrosa          #+#    #+#             */
/*   Updated: 2025/03/12 15:40:03 by rpedrosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/parsing.h"
#include "../../incs/minishell.h"

static int expande(char **s, int x)
{
	char *prev;
	char *env;
	char *temp;
	int free_flag;
	
	free_flag = 0;
	prev = NULL;
	if (x > 1)
	{
		prev = ft_substr(*s, 0, x - 1);
		if (prev == NULL)
			return (print_error(MALLOC_ERROR), 1);
	}
	my_getenv(s, &env, &x, &free_flag);
	temp = ft_strjoin(prev, env);
	if (temp == NULL)
		return (print_error(MALLOC_ERROR), 1);
	free(*s);
	*s = ft_strdup(temp);
	if (prev != NULL)
		free_flag = 1;
	if (ft_strncmp(env, "", 1))
		free_flag = 2;
	free_expand(&temp, &prev, &env, free_flag);
	return (0);
}

static int	expande_red_util(char *file)
{
	int	i;
	
	i = -1;
	if (quote_counter(file) % 2 != 0)
			return (print_error(QUOTE_ERROR), 1);
	while (file[++i])
	{
		if (file[i] == 34 \
			|| file[i] == 39)
			i += skip_quotes(file, i);
		if (file[i] == '$')
		{
			if (expande(&file, i + 1) != 0)
				return (1);
		if (ft_strncmp(file, "", 1) == 0)
			return (print_error(SYNTAX_ERROR), 1);
		}
	}
	return (0);
}
static int expande_red(t_simple_command *s)
{
	if (s->infile)
	{
	if (expande_red_util(s->infile) != 0)
			return (1);
	}
	if (s->outfile)
	{
		if (expande_red_util(s->outfile) != 0)
			return (1);
	}
	if (s->double_in)
	{
		if (expande_red_util(s->double_in) != 0)
			return (1);
	}
	if (s->double_out)
	{
		if (expande_red_util(s->double_out) != 0)
			return (1);
	}
	return (0);
}
static int expand_args(t_command *command, int i)
{
	int	j;
	int	x;

	x = -1;
	j = -1;
	while (command->table[i]->args[++j])
	{
		if (quote_counter(command->table[i]->args[j]) % 2 != 0)
			return (print_error(QUOTE_ERROR), 1);
		while (command->table[i]->args[j][++x])
		{
			if (command->table[i]->args[j][x] == 34 \
				|| command->table[i]->args[j][x] == 39)
				x += skip_quotes(command->table[i]->args[j], x);
			if (command->table[i]->args[j][x] == '$')
			{
				if (expande(&command->table[i]->args[j], x + 1) != 0)
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
		if (expande_red(command->table[i]) != 0)
			return (1);
		if (expand_args(command, i) != 0)
			return (1);
	}
	return (0);
}
