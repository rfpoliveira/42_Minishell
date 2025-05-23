/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reorganize_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpedrosa <rpedrosa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 12:01:42 by rpedrosa          #+#    #+#             */
/*   Updated: 2025/05/23 13:45:23 by rpedrosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"
#include "../../incs/parsing.h"

/**
 @brief counts the number of arguments were you have a single redirect 
        that will be deleted and returns them
 @note we need to take in consideracion some case will delite multiple args
        echo test > file
        other the number of args will be the same 
        (we only delete part of the arg): echo test>file 
*/
static int	count_singles(char **args, int curr_arg, int curr_chr)
{
	if (args[curr_arg][curr_chr + 1] == '\0')
	{
		if (curr_chr > 0)
			return (1);
		else
			return (2);
	}
	else
	{
		if (curr_chr > 0)
			return (0);
		else
			return (1);
	}
}

/**
 @brief counts the number of arguments were you have a double redirect 
        that will be deleted and returns them
 @note we need to take in consideracion some case will delite multiple args: 
     echo test >> file
    other the number of args will be the same 
	(we only delete part of the arg)
    echo test>>file 
*/
static int	count_doubles(char **args, int curr_arg, int curr_chr)
{
	if (args[curr_arg][curr_chr + 2] == '\0')
	{
		if (curr_chr > 0)
			return (1);
		else
			return (2);
	}
	else
	{
		if (curr_chr > 0)
			return (0);
		else
			return (1);
	}
}

/**
 @brief counts the number of arguments left after we delete 
        what we dont need (the args with redirect and the file names)
 @return the number of arguments left after the deletion 
*/
int	new_arg_counter(t_simple_command *table, char **args)
{
	int	i;
	int	j;
	int	count;

	i = -1;
	j = -1;
	count = 0;
	while (args[++i])
	{
		while (args[i][++j])
		{
			if (args[i][j] == '<' || args[i][j] == '>')
			{
				if (args[i][j + 1] == '<' || args[i][j + 1] == '>')
				{
					count += count_doubles(args, i, j);
					j++;
				}
				else
					count += count_singles(args, i, j);
			}
		}
		j = -1;
	}
	return (table->number_args - count);
}

/**
 @brief takes each argument and copys to tmp everything which is not a
         redirect i iterate all the arg, if it finds a symbol it stops.
		 
            if it stops in the first arg(i = 0) and is not the first chr 
            (j != 0) we can save what comes before the symbol
            pass that point we check if we did get to null 
            (!current->args[i][j]), telling us that the loop did not find 
            anything, then check if the previous arg add symbols in the 
            last chars to make sure the current args is not a redirection, 
            if all this is true we can copy.
			
 @param tmp is where we save the new argument.
 @param current is the table we are working on.
 @param i is used to iterate, inicialize before because of the norm.
 @return 0 in case of success,
         1 or any other number in case of error 
*/
int	populate_tmp(char **tmp, t_data *command, t_simple_command *current, int i)
{
	int	j;
	int	curr_tmp;
	int	last_chr_idx;

	j = 0;
	last_chr_idx = 0;
	curr_tmp = -1;
	while (current->args[++i])
	{
		while (current->args[i][j] && current->args[i][j] != '<' && \
		current->args[i][j] != '>')
			j++;
		if ((j != 0 && i == 0) || \
		(!current->args[i][j] && (current->args[i - 1][last_chr_idx] != '<' && \
		current->args[i - 1][last_chr_idx] != '>')))
		{
			tmp[++curr_tmp] = copy_red(current->args[i]);
			if (tmp[curr_tmp] == NULL)
				return (print_error(MALLOC_ERROR, &command->exit_code), 1);
		}
		last_chr_idx = ft_strlen(current->args[i]) - 1;
		j = 0;
	}
	return (0);
}
