/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reorganize_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpedrosa <rpedrosa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 12:01:42 by rpedrosa          #+#    #+#             */
/*   Updated: 2025/07/07 16:15:23 by rpedrosa         ###   ########.fr       */
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
	if (args[curr_arg][curr_chr] != '\0' \
&& args[curr_arg][curr_chr + 1] != '\0' \
&& args[curr_arg][curr_chr + 2] == '\0')
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
	count = 0;
	while (args[++i])
	{
		j = -1;
		while (args[i][++j])
		{
			if (args[i][j] == 34 || args[i][j] == 39)
				j += skip_quotes(args[i], j);
			if (args[i][j] == '<' || args[i][j] == '>')
			{
				if (args[i][j + 1] == '<' || args[i][j + 1] == '>')
					count += count_doubles(args, i, j++);
				else
					count += count_singles(args, i, j);
			}
		}
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
 @param cur is the table we are working on.
 @param i is used to iterate, inicialize before because of the norm.

 lsx is the last char index;
 @return 0 in case of success,
         1 or any other number in case of error 
*/

int	copy_util(t_data *command, char **tmp, char **cur)
{
	*tmp = ft_strdup(*cur);
	if (*tmp == NULL)
		return (print_error(MALLOC_ERROR, &command->exit_code), 1);
	return (0);
}

int	populate_tmp(char **tmp, t_data *command, char **cur, int i)
{
	int	j;
	int	cur_tmp;
	int	lsx;

	lsx = 0;
	cur_tmp = 0;
	while (cur[++i])
	{
		j = 0;
		while (cur[i][j] && cur[i][j] != '<' && cur[i][j] != '>')
		{
			if (cur[i][j] == 34 || cur[i][j] == 39)
				j += skip_quotes(cur[i], j) - 1;
			j++;
		}
		if ((j != 0 && i == 0) || \
(j != 0 && cur[i][j] == '>') || (j != 0 && cur[i][j] == '<') || \
(!cur[i][j] && (cur[i - 1][lsx] != '<' && cur[i - 1][lsx] != '>')))
		{
			if (copy_util(command, &tmp[cur_tmp++], &cur[i]) != 0)
				return (1);
		}
		lsx = ft_strlen(cur[i]) - 1;
	}
	return (0);
}
