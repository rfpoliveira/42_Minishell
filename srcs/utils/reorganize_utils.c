/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reorganize_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpedrosa <rpedrosa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 12:01:42 by rpedrosa          #+#    #+#             */
/*   Updated: 2025/04/17 12:08:26 by rpedrosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

/* @brief: counts the number of arguments were you have a single redirect that will be deleted and returns them
   @notes: we need to take in consideracion some case will delite multiple args: echo test > file
           other the number of args will be the same (we only delete part of the arg): echo test>file 
*/
static int count_singles(char **args, int curr_arg, int curr_chr)
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
/* @brief: counts the number of arguments were you have a double redirect that will be deleted and returns them
@notes: we need to take in consideracion some case will delite multiple args: echo test >> file
           other the number of args will be the same (we only delete part of the arg): echo test>>file */
static int count_doubles(char **args, int curr_arg, int curr_chr)
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
/* @brief: counts the number of arguments left after we delete what we dont need (the args with redirect and the file names)
    @return: will return the number of arguments left after the deletion */
int new_arg_counter(t_simple_command *table, char **args)
{
    int i;
    int j;
    int count;

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
/* @brief: takes each argument and copys to tmp everything which is not a redirect
           in case of for exemple: test>file we maintain part of the string and use substring
           in case of "> file" we need to skip the 2 arguments (1 in the consicion and the other normally in the loop)
           in any other case we simply copy the arg as we will keep it 
    @return: 0 in case of success
            1 or any other number in case of error */
int    populate_tmp(char **tmp, t_data *command, t_simple_command *current)
{
    int i;
    int j;
    int curr_tmp;

    i = 0;
    j = -1;
    curr_tmp = -1;
    while (current->args[i])
    {
        while (current->args[i][++j])
        {
            if (current->args[i][j] == '<' || current->args[i][j] == '>')
            {
                if (current->args[i][j + 1] != '\0' && j > 0)
                {
                    tmp[++curr_tmp] = ft_substr(current->args[i], 0, j);
                    if (tmp[curr_tmp] == NULL)
                        return (print_error(MALLOC_ERROR, &command->exit_code), 1);
                }
                else if ((j == 0 && ((current->args[i][j + 1] == '<' || \
                current->args[i][j + 1] == '>' ) && \
                current->args[i][j + 2] == '\0')) || \
                (j == 0 && current->args[i][j + 1] == '\0'))
                    i++;
                else if (current->args[i][j + 1] == '\0' && j != 0)
                {
                    tmp[++curr_tmp] = ft_strdup(current->args[i]);
                    i++;
                }
                else
                    i++;
                break ;
            }
        }
        if (current->args[i])
        {
            if (current->args[i][j] == '\0')
            {
                tmp[++curr_tmp] = ft_strdup(current->args[i]);
                if (tmp[curr_tmp] == NULL)
                    return (print_error(MALLOC_ERROR, &command->exit_code), 1);
            }
        }
        if (!current->args[i])
            break ;
        i++;
        j = -1;
    }
    return (0);
}
