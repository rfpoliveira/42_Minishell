/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpedrosa <rpedrosa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 16:08:04 by rpedrosa          #+#    #+#             */
/*   Updated: 2025/05/07 15:47:40 by rpedrosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/parsing.h"

/* @brief: checks for quotes in the expanding process 
			and correctly skips them or not
	@args: flag is for checking if we are bettewn double quotes or not
			i is for iterating in the current string being checked
			current is the current string being checked
	return: 0 if the string as not ended.
			1 to signal the string as ended making the loop or the main function
			break
	@note: used in expand_red_util and expand_args at expander.c
*/

int	mid_expand_quote_handler(int *flag, int *i, char *current)
{
	if (current[*i] == 34)
		(*flag)++;
	if (current[*i] == 39 && (*flag % 2 == 0))
		*i += skip_quotes(current, *i);
	if (!current[*i])
		return (1);
	return (0);
}

static	int copy_n_iter(char **new_matrix, t_simple_command *curr, int *i, int x)
{
	new_matrix[*i] = ft_strdup(curr->args[x]);
	if (!new_matrix[(*i)++])
		return (1);
	return (0);
}

static	int populate_matrix(char **new_matrix, t_simple_command *curr, char **tmp, int *i)
{	
	int	j;
	int curr_arg;
	int	x;
	int error;
	
	curr_arg = *i;
	j = 0;
	x = -1;
	error = 0;
	while(tmp[j])
	{
		new_matrix[*i] = tmp[j++];
		if (!new_matrix[(*i)++])
			return (1);
	}
	*i = 0;
	while(curr->args[++x])
	{
		if (*i == curr_arg)
			*i += j;
		else
			error = copy_n_iter(new_matrix, curr, i, x);
	}
	return (error);
}

static int	reorganize_matrix(t_simple_command *curr, int curr_arg, int *exit_code)
{
	char 	**tmp;
	char 	**new_matrix;
	int		i;
	
	i = 0;
	tmp = whitespaces_split(curr->args[curr_arg]);
	if (!tmp)
		return (print_error(MALLOC_ERROR, exit_code), 1);
	while (tmp[i])
		i++;
	new_matrix = malloc(sizeof(char *) * (curr->number_args + i));
	if (!new_matrix)
		return (print_error(MALLOC_ERROR, exit_code), 1);
	i = curr_arg;
	if (populate_matrix(new_matrix, curr, tmp, &i))
		return (matrix_free(new_matrix), matrix_free(tmp), print_error(MALLOC_ERROR, exit_code), 1);
	new_matrix[i] = NULL;
	free(tmp);
	matrix_free(curr->args);
	curr->args = new_matrix;
	return (0);
}

int sep_per_words(t_simple_command *curr_table, int *exit_code)
{
	int		i;
	int		j;

	j = 0;
	i = -1;
	while(curr_table->args[++i])
	{
		while(curr_table->args[i][j])
		{
			if (curr_table->args[i][j] == 34 || curr_table->args[i][j] == 39)
				j += skip_quotes(curr_table->args[i], j);
			if (ft_isspace(curr_table->args[i][j]))
			{
				if (reorganize_matrix(curr_table, i, exit_code))
					return (1);
				i = -1;
				j = 0;
				break ;
			}
			if (curr_table->args[i][j])
				j++;
		}
		j = 0;
	}
	return (0);
}
