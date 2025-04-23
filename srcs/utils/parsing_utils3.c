/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpedrosa <rpedrosa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 10:43:54 by rpedrosa          #+#    #+#             */
/*   Updated: 2025/04/23 18:20:45 by rpedrosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"
#include "../../incs/parsing.h"
/* @brief: inicialize every matrix need to save the files
	@arguments: command is the main struct with all the data
                splited is the user input after being separated by pipes
                curr_table is the current table we are inicializing
*/
void	ini_files(t_data *command, char **splited, int curr_table)
{
	int	count;

	count = count_infiles(splited);
	while (count >= 0)
		command->table[curr_table]->infile[count--] = NULL;
	count = count_outfiles(splited);
	while (count >= 0)
		command->table[curr_table]->outfile[count--] = NULL;
	count = count_double_outs(splited);
	while (count >= 0)
		command->table[curr_table]->double_out[count--] = NULL;
	count = count_double_ins(splited);
	while (count >= 0)
		command->table[curr_table]->double_in[count--] = NULL;
}
/* @brief: alloc and inicialize every matrix need to save the files
	@arguments: command is the main struct with all the data
                splited is the user input after being separated by pipes
                curr_table is the current table we are inicializing
    @return: 0 in case of success.
             1 or any other number in case of error.
*/

int	alloc_file(t_data *command, char **splited, int curr_table)
{
	command->table[curr_table]->infile = malloc(sizeof(char *) * \
										(count_infiles(splited) + 1));
	command->table[curr_table]->outfile = malloc(sizeof(char *) * \
										(count_outfiles(splited) + 1));
	command->table[curr_table]->double_in = malloc(sizeof(char *) * \
										(count_double_ins(splited) + 1));
	command->table[curr_table]->double_out = malloc(sizeof(char *) * \
										(count_double_outs(splited) + 1));
	if (command->table[curr_table]->infile == NULL || \
	command->table[curr_table]->outfile == NULL || \
	command->table[curr_table]->double_in == NULL || \
	command->table[curr_table]->double_out == NULL)
		return (print_error(MALLOC_ERROR, &command->exit_code), 1);
	ini_files(command, splited, curr_table);
	return (0);
}
/* @brief: checks if there is a even number of quotes.
	@arguments: s is the current string (arg or file) being checked
				exit_code saves the exit code of the last command
	if we have and unclosed quote we give an error
	if that quote is bettewn other quotes it should be ignored
	@return: 0 in case of success
			 1 or any other number in case of errors. 
*/

static void	quote_counter_util(char **s, int *i, int *j, int *count)
{
	int	flag;

	flag = 0;
	flag = s[*j][*i];
	(*count)++;
	if (s[*j][(*i) + 1] != '\0')
		*i += skip_quotes(s[*j], *i);
	if (s[*j][(*i) - 1] == flag)
		(*count)++;
}

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
				quote_counter_util(s, &i, &j, &count);
			if (!s[j][i])
				break ;
		}
	}
	if (count % 2 == 0)
		return (0);
	else
		return (print_error(QUOTE_ERROR, exit_code), 1);
}
