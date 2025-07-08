/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpedrosa <rpedrosa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 14:53:37 by rpedrosa          #+#    #+#             */
/*   Updated: 2025/07/08 18:52:41 by rpedrosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/parsing.h"
#include "../../incs/minishell.h"

/**
 *  @brief this expandes whats asked maintaining what comes before the "$"
 * 
 * get_prev saves anything before the "$"
 * my_get_env gets the information that need to get expanded.
 * get_str puts the whole thing together.
 * "$?" -> expandes to the last command exit code;
 * "$$" -> usually expands to pid but since we cant get it we
 * ignore it.
 *
 *	@param s pointer to the "$" in the string.
 * 	@param x position in the string next to the "$"
 * 	@param exit_code is the exit code of the last command.
 *	@return 0 in case of sucesss,
 *	MALLOC_ERROR or any number != 0 in case of any error 
*/
static int	expande(char **s, int x, t_data *data)
{
	char	*prev;
	char	*env;
	int		len;

	x++;
	prev = get_prev(*s, x);
	if (!prev)
		return (print_error(MALLOC_ERROR, &data->exit_code), MALLOC_ERROR);
	if (my_get_env(*s, &env, x, data) != 0)
		return (print_error(MALLOC_ERROR, &data->exit_code), MALLOC_ERROR);
	len = ft_strlen(prev) + ft_strlen(env) + 1;
	if (get_str(s, prev, env, len) != 0)
		return (print_error(MALLOC_ERROR, &data->exit_code), MALLOC_ERROR);
	ft_free(&prev);
	ft_free(&env);
	return (0);
}

/**
 * @brief is called to iterate threw the redirection saved
 * @param file is the current redirection being checked.
 * @param exit_code is the exit code of the last command.
 * @param i is to iterate in the loops
 * @param j is to iterate in the loops
 *
 * @note if "$" is found expand whats next: if there is another "$" ignores
 * ignores anything bettewn quotes (not double quotes this time)
 *
 * @return 0 in case of sucesss,
 * 1 in case of any error (is error if something expandes to "")
*/
static int	expande_red_util(char **file, int i, int j, t_data *data)
{
	int	flag;

	flag = 0;
	while (*file && file[j])
	{
		while (file[j][i])
		{
			if (mid_expand_quote_handler(&flag, &i, file[j]) != 0)
				break ;
			if (file[j][i] == '$')
			{
				if (expande(&file[j], i, data) != 0)
					return (1);
				if (ft_strncmp(file[j], "", 1) == 0)
					return (print_error(AMBI_REDI, &data->exit_code), 1);
				i = -1;
				flag = 0;
			}
			i++;
		}
		j++;
		i = 0;
	}
	return (0);
}

/** 
 * @brief is called to check if there are redirections saved
 * @param curr_table is the current table being checked.
 * @param exit_code is the exit code of the last command.
 * @return 0 in case of sucesss
		 	1 in case of any error 
*/
static int	expande_red(t_simple_command *curr_table, t_data *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (curr_table->infile && \
expande_red_util(curr_table->infile, i, j, data) != 0)
		return (1);
	if (curr_table->outfile && \
expande_red_util(curr_table->outfile, i, j, data) != 0)
		return (1);
	if (curr_table->double_out && \
expande_red_util(curr_table->double_out, i, j, data) != 0)
		return (1);
	return (0);
}

/**expande_red anything bettewn quotes or double quotes
 * 
 * @return 0 in case of sucesss,
		 	 1 in case of any error 
*/
static int	expand_args(t_simple_command *curr_table, t_data *data)
{
	int	j;
	int	x;
	int	flag;

	j = -1;
	while (curr_table->args[++j])
	{
		flag = 0;
		x = -1;
		while (curr_table->args[j][++x])
		{
			if (mid_expand_quote_handler(&flag, &x, curr_table->args[j]) != 0)
				break ;
			if (curr_table->args[j][x] == '$' && curr_table->args[j][x + 1] \
&& !ft_isspace(curr_table->args[j][x + 1]) \
&& curr_table->args[j][x + 1] != 34)
			{
				if (expande(&curr_table->args[j], x, data) != 0)
					return (1);
				x = -1;
				flag = 0;
			}
		}
	}
	return (0);
}

/**
 * @brief iterates the tables and calls helper functions to find
 * stuff to expand in the arguments and redirects saved
 *
 * @return 0 in case of success,
 * 1 in case of any error
*/
int	handle_expanding(t_data *command)
{
	int	i;

	i = -1;
	while (command->table[++i])
	{
		if (expande_red(command->table[i], command) != 0)
			return (1);
		if (expand_args(command->table[i], command) != 0)
			return (1);
		if (sep_per_words(command->table[i], &command->exit_code) != 0)
			return (1);
	}
	return (0);
}
