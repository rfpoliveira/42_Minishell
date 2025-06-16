/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpedrosa <rpedrosa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 16:08:04 by rpedrosa          #+#    #+#             */
/*   Updated: 2025/06/16 11:56:45 by rpedrosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/parsing.h"

/**
 @brief checks for quotes in the expanding process 
		and correctly skips them or not
 @param flag is for checking if we are bettewn double quotes or not
 @param i is for iterating in the current string being checked
		 current is the current string being checked
 @return 0 if the string as not ended,
		 1 to signal the string as ended making the loop or the main function
		break
 @note used in expand_red_util and expand_args at expander.c
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

/**
 @brief copies the args from the old to the new matrix
		 malloc is protected as well and i is incremented
 @param curr current table being checked
 @param new_mtx pointer to the new matrix
 @param x is the index of the old matrix that we will copied
 @param i is current index of the new matrix
 @return 0 in case of success,
		 1 if there is any malloc errors
*/
static int	copy_n_iter(char **new_mtx, t_simple_command *curr, int *i, int x)
{
	new_mtx[*i] = ft_strdup(curr->args[x]);
	if (!new_mtx[(*i)++])
		return (1);
	return (0);
}

/**
 @brief constructs the new matrix with the arguments to keep
		and the new separated ones
 @param curr current table being checked
 @param new_mtx pointer to the new matrix
 @param tmp argument to add after being separated
 @param i is the of the argument that was separated
 @return 0 in case of success,
		 1 if there is any malloc errors
*/
static int	pop_mtx(char **new_mtx, t_simple_command *curr, char **tmp, int *i)
{
	int	j;
	int	curr_arg;
	int	x;
	int	error;

	curr_arg = *i;
	j = 0;
	x = -1;
	error = 0;
	while (tmp[j])
	{
		new_mtx[*i] = tmp[j++];
		if (!new_mtx[(*i)++])
			return (1);
	}
	*i = 0;
	while (curr->args[++x])
	{
		if (*i == curr_arg)
			*i += j;
		else
			error = copy_n_iter(new_mtx, curr, i, x);
	}
	return (error);
}

/** 
 @brief creats the new matrix and replaces the one with the non seprated
		arguments
 @param curr current table being checked
 @param curr_arg the index of the argument to be splitted
 @param exit_code the exit code of the last command
 @return 0 in case of success,
		 1 if there is any malloc errors
*/
static int	reorg_mtx(t_simple_command *curr, int curr_arg)
{
	char	**tmp;
	char	**new_matrix;
	int		i;

	i = 0;
	tmp = whitespaces_split(curr->args[curr_arg]);
	if (!tmp)
		return (1);
	while (tmp[i])
		i++;
	new_matrix = malloc(sizeof(char *) * (curr->number_args + i));
	if (!new_matrix)
		return (1);
	i = curr_arg;
	if (pop_mtx(new_matrix, curr, tmp, &i))
		return (matrix_free(new_matrix), matrix_free(tmp), 1);
	new_matrix[i] = NULL;
	ft_free(tmp);
	matrix_free(curr->args);
	curr->args = new_matrix;
	return (0);
}

/**
 @brief in case there are spaces after expanding
		it sperates the args
 @param curr_table -> current table being checked
 @param exit_code -> exit code of the last commmand
 @return 0 in case of success,
		 1 if there is any malloc errors
*/
int	sep_per_words(t_simple_command *curr_table, int *exit_code)
{
	int		i;
	int		j;

	j = 0;
	i = -1;
	while (curr_table->args[++i])
	{
		while (curr_table->args[i][j])
		{
			if (curr_table->args[i][j] == 34 || curr_table->args[i][j] == 39)
				j += skip_quotes(curr_table->args[i], j);
			if (ft_isspace(curr_table->args[i][j]))
			{
				if (reorg_mtx(curr_table, i))
					return (print_error(MALLOC_ERROR, exit_code), 1);
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
