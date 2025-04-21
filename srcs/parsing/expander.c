/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpedrosa <rpedrosa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 14:53:37 by rpedrosa          #+#    #+#             */
/*   Updated: 2025/04/21 18:31:21 by rpedrosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/parsing.h"
#include "../../incs/minishell.h"

/* @brief: this expandes whats asked maintaining what comes before the "$"
	@arguments: s is a pointer to the "$" in the string.
				x is position in the string next to the "$"
				exit_code is the exit code of the last command.
	get_prev saves anything before the "$"
	my_get_env gets the information that need to get expanded.
	get_str puts the whole thing together.
	@notes:"$?" -> expandes to the last command exit code;
	@return: 0 in case of sucesss
		 	 MALLOC_ERROR or any number != 0 in case of any error 
*/

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
/* @brief: is called to iterate threw the redirection saved.
	@arguments: file is the current redirection being checked.
				exit_code is the exit code of the last command.
				i and j are to iterate in the loops, 
				they are declared and inicialized previously to use fewer lines here (42 norm)
	if "$" is found expand whats next: if there is another "$" ignores,
	ignores anything bettewn quotes (not double quotes this time)
	@return: 0 in case of sucesss
		 	 1 in case of any error (is error if something expandes to "")
*/

static int	expande_red_util(char **file, int i, int j, int *exit_code)
{
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
/* @brief: is called to check if there are redirections saved
	@arguments: curr_table is the current table being checked.
				exit_code is the exit code of the last command.
	@return: 0 in case of sucesss
		 	 1 in case of any error 
*/

static int	expande_red(t_simple_command *curr_table, int *exit_code)
{
	int	i;
	int	j;
	int	error;

	i = -1;
	j = -1;
	error = 0;
	if (curr_table->infile)
		error = expande_red_util(curr_table->infile, i, j, exit_code) != 0;
	if (curr_table->outfile)
		error = expande_red_util(curr_table->outfile, i, j, exit_code) != 0;
	if (curr_table->double_in)
		error = expande_red_util(curr_table->double_in, i, j, exit_code) != 0;
	if (curr_table->double_out)
		error = expande_red_util(curr_table->double_out, i, j, exit_code) != 0;
	return (error);
}

/* @brief: is called to iterate all the arguments and look for expansions
	@arguments: curr_table is the current table being checked.
				exit_code is the exit code of the last command.
	@notes: if "$" is found expand whats next: if there is another "$" ignores,
	ignores anything bettewn quotes or double quotes
	@return: 0 in case of sucesss
		 	 1 in case of any error 
*/

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

/* @brief: iterates the tables and calls helper functions to find
	stuff to expand in the arguments and redirects saved
	@return: 0 in case of success
			 1 in case of any error
	@notes: the errors messages are called when the error is found 
*/

int	handle_expanding(t_data *command)
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
