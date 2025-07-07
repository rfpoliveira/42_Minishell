/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpedrosa <rpedrosa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 10:43:54 by rpedrosa          #+#    #+#             */
/*   Updated: 2025/07/07 16:13:00 by rpedrosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"
#include "../../incs/parsing.h"

/**
 @brief inicialize every matrix need to save the files
 @param command is the main struct with all the data
 @param splited is the user input after being separated by pipes
 @param curr_table is the current table we are inicializing
*/
static void	ini_files(t_data *command, int curr_table)
{
	int	count;

	count = command->table[curr_table]->numb_ins;
	while (count >= 0)
		command->table[curr_table]->infile[count--] = NULL;
	count = command->table[curr_table]->numb_outs;
	while (count >= 0)
		command->table[curr_table]->outfile[count--] = NULL;
	count = command->table[curr_table]->numb_double_outs;
	while (count >= 0)
		command->table[curr_table]->double_out[count--] = NULL;
	count = command->table[curr_table]->numb_double_ins;
	while (count >= 0)
		command->table[curr_table]->double_in[count--] = NULL;
	command->table[curr_table]->iters = malloc(sizeof(t_iters));
	command->table[curr_table]->iters->in_iter = 0;
	command->table[curr_table]->iters->out_iter = 0;
	command->table[curr_table]->iters->double_out_iter = 0;
}

/**
 @brief alloc and inicialize every matrix need to save the files
 @param command is the main struct with all the data
 @param splited is the user input after being separated by pipes
 @param curr_table is the current table we are inicializing
 @return 0 in case of success,
         1 or any other number in case of error.
*/
int	alloc_file(t_data *command, int curr_table)
{
	command->table[curr_table]->infile = NULL;
	command->table[curr_table]->outfile = NULL;
	command->table[curr_table]->double_in = NULL;
	command->table[curr_table]->double_out = NULL;
	command->table[curr_table]->infile = malloc(sizeof(char *) \
* (command->table[curr_table]->numb_ins) + 8);
	command->table[curr_table]->outfile = malloc(sizeof(char *) \
* (command->table[curr_table]->numb_outs) + 8);
	command->table[curr_table]->double_in = malloc(sizeof(char *) \
* (command->table[curr_table]->numb_double_ins) + 8);
	command->table[curr_table]->double_out = malloc(sizeof(char *) \
* (command->table[curr_table]->numb_double_outs) + 8);
	ini_files(command, curr_table);
	return (0);
}

/**
 @brief skips the quotes found until the next one and ajusts the count
 @param s is the current matrix (arg or file) being checked
 @param j current string in the matrix
 @param i the index in the string
 @param count is the number of quotes
*/
static void	quote_counter_util(char **s, int *i, int *j, int *count)
{
	int	flag;

	flag = s[*j][*i];
	(*count)++;
	if (s[*j][(*i) + 1] != '\0')
		*i += skip_quotes(s[*j], *i);
	else
	{
		(*i)++;
		return ;
	}
	if (s[*j][(*i) - 1] == flag)
		(*count)++;
}

/**
 @brief checks if there is a even number of quotes.
  
	if we have and unclosed quote we give an error
	if that quote is bettewn other quotes it should be ignored

 @param s is the current matrix (arg or file) being checked
 @param exit_code saves the exit code of the last command
 @return 0 in case of success
			 1 or any other number in case of errors. 
*/
int	quote_counter(char **s, int *exit_code)
{
	int	i;
	int	j;
	int	count;

	i = -1;
	j = -1;
	count = 0;
	if (!s)
		return (0);
	while (s[++j])
	{
		while (s[j][++i])
		{
			if (s[j][i] == 34 || s[j][i] == 39)
			{
				quote_counter_util(s, &i, &j, &count);
				i--;
			}
		}
		i = -1;
	}
	if (count % 2 == 0)
		return (0);
	else
		return (print_error(QUOTE_ERROR, exit_code), 1);
}
