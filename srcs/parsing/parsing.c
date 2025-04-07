/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpedrosa <rpedrosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 16:50:50 by rpedrosa          #+#    #+#             */
/*   Updated: 2025/04/07 16:35:16 by rpedrosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"
#include "../../incs/parsing.h"

int	ini_file(t_command *command, int table)
{
	char **current;

	current = command->table[table]->args;
	command->table[table]->infile = \
	malloc(sizeof(char *) * count_infiles(current) + 1);
	command->table[table]->outfile = \
	malloc(sizeof(char *) * count_outfiles(current) + 1);
	command->table[table]->double_in = \
	malloc(sizeof(char *) * count_double_ins(current) + 1);
	command->table[table]->double_out = \
	malloc(sizeof(char *) * count_double_outs(current) + 1);
	if (command->table[table]->infile == NULL\
	command->table[table]->outfile == NULL\
	command->table[table]->double_in == NULL\
	command->table[table]->double_out == NULL)
		return (print_error(MALLOC_ERROR, command->exit_code), 1);
	command->table[table]->outfile[0] = NULL;
	command->table[table]->infile[0] = NULL;
	command->table[table]->double_in[0] = NULL;
	command->table[table]->double_out[0] = NULL;
	return (0);
}
// puts everything separated by pipes and spaces ready to be parsed
static void mount_table(t_command *command, char **splited)
{
	int i;

	i = 0;
	while (i < command->number_simple_commands)
	{
		command->table[i] = malloc(sizeof(t_simple_command));
		if (!command->table[i])
			return (memory_free(&command->exit_code, splited, command, MALLOC_ERROR));
		command->table[i]->args = whitespaces_split(splited[i]);
		if (!(command->table[i]->args))
			return (memory_free(&command->exit_code, splited, command, MALLOC_ERROR));
		command->table[i]->number_args = count_args(command->table[i]);
		if (ini_file(command, i) != 0)
			return (memory_free(&command->exit_code, splited, command, MALLOC_ERROR));	
		i++;
	}
}

// inicializacion of the main structure
static void ini_command(char **splited, t_command *command)
{
	int i;

	i = 0;
	while (splited[i])
		i++;
	command->number_simple_commands = i;
	command->table = malloc(sizeof(t_simple_command) * i + 8);
	if (!command->table)
		return (memory_free(&command->exit_code, splited, command, MALLOC_ERROR));
	command->table[i] = NULL;
	if (quote_counter(splited, &command->exit_code) != 0)
		return (memory_free(&command->exit_code, splited, command, 0));
	mount_table(command, splited);
}
// calls everything in the following order:
/* check_first_pipe to check if there is a pipe in the beggining
parsing_split to split by pipes
ini_command for allocating most of the memory and inicializing the main struct
handle_redirect to put any redirections on the correct place in the strcut
handle_expanding for expande everything correctly
handle_quotes for deleting quotes since we dont be needing them anymore
and parse command to check if the commands exist or not
if any of this returns any error the programs stops and calls memory free */

t_command *parsing(char *s, t_command *command)
{
	char **splited;
	int i;

	i = 1;
	if (!s)
		return (NULL);
	if (check_pipes(s) == 0)
		return (ft_free(&s), memory_free(&i, NULL, NULL, SYNTAX_ERROR), NULL);
	splited = parsing_split(s, '|');
	if (!splited)
		return (ft_free(&s), memory_free(&i, NULL, NULL, MALLOC_ERROR), NULL);
	ini_command(splited, command);
	if (!command->table)
		return (ft_free(&s), NULL);
	/* 	if (handle_redirect(command) != 0)
			return (ft_free(&s), memory_free(&command->exit_code, splited, command, 0), NULL); */
	if (handle_expanding(command) != 0)
		return (ft_free(&s), memory_free(&command->exit_code, splited, command, 0), NULL);
	if (handle_quotes(command) != 0)
		return (ft_free(&s), memory_free(&command->exit_code, splited, command, 0), NULL);
	/* if (parse_commands(command) != 0)
		return (ft_free(&s), memory_free(&command->exit_code, splited, command, 0), NULL); */
	return (ft_free(&s), matrix_free(splited), command);
}
