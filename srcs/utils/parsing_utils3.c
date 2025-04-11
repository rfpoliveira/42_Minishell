/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpedrosa <rpedrosa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 10:43:54 by rpedrosa          #+#    #+#             */
/*   Updated: 2025/04/11 15:51:43 by rpedrosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"
#include "../../incs/parsing.h"

int	alloc_file(t_data *command, char **splited, int curr_table)
{
	command->table[curr_table]->infile = malloc(sizeof(char *) * (count_infiles(splited) + 1));
	command->table[curr_table]->outfile = malloc(sizeof(char *) * (count_outfiles(splited) + 1));
	command->table[curr_table]->double_in = malloc(sizeof(char *) * (count_double_ins(splited) + 1));
	command->table[curr_table]->double_out = malloc(sizeof(char *) * (count_double_outs(splited) + 1));
	if (command->table[curr_table]->infile == NULL ||\
	command->table[curr_table]->outfile == NULL ||\
	command->table[curr_table]->double_in == NULL ||\
	command->table[curr_table]->double_out == NULL)
		return (print_error(MALLOC_ERROR, &command->exit_code), 1);
    command->table[curr_table]->infile[0] = NULL;
	command->table[curr_table]->outfile[0] = NULL;
	command->table[curr_table]->double_in[0] = NULL;
	command->table[curr_table]->double_out[0] = NULL;
	return (0);
}