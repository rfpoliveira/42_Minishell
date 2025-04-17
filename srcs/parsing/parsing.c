/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpedrosa <rpedrosa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 16:50:50 by rpedrosa          #+#    #+#             */
/*   Updated: 2025/04/11 16:14:15 by rpedrosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"
#include "../../incs/parsing.h"

static void mount_table(t_data *command, char **splited)
{
	int i;


	i = 0;
	while (i < command->number_simple_commands)
	{
		command->table[i] = malloc(sizeof(t_simple_command));
		if (!command->table[i])
			return (memory_free(splited, command, MALLOC_ERROR));
		command->table[i]->args = whitespaces_split(splited[i]);
		if (!(command->table[i]->args))
			return (memory_free(splited, command, MALLOC_ERROR));
		command->table[i]->number_args = count_args(command->table[i]);
		if (alloc_file(command, splited, i) != 0)
			return (memory_free(splited, command, MALLOC_ERROR));
		i++;
	}
}
// inicializacion of the main structure
static void ini_command(char **splited, t_data *command)
{
	int i;

	i = 0;
	while (splited[i])
		i++;
	command->number_simple_commands = i;
	command->table = malloc(sizeof(t_simple_command) * i + 8);
	if (!command->table)
		return (memory_free(splited, command, MALLOC_ERROR));
	command->table[i] = NULL;
	mount_table(command, splited);
	if (quote_counter(splited, &command->exit_code) != 0)
		return (memory_free(splited, command, 0));
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


int parsing(char **user_line, t_data *command)
{
	char **splited;

	if (!*user_line || !ft_strncmp(*user_line, "", 1))
		return (1);
	if (check_pipes(*user_line) == 0)
		return (ft_free(user_line), memory_free(NULL, command, SYNTAX_ERROR), 1);
	splited = parsing_split(*user_line, '|');
	if (!splited)
		return (ft_free(user_line), memory_free(NULL, command, MALLOC_ERROR), 1);
	ft_free(user_line);
	ini_command(splited, command);
	if (!command->table)
		return (1);
	if (handle_redirect(command) != 0)
		return (memory_free(splited, command, 0), 1);
	if (handle_expanding(command) != 0)
		return (memory_free(splited, command, 0), 1);
	if (handle_quotes(command) != 0)
		return (memory_free(splited, command, 0), 1);
	/* if (parse_commands(command) != 0)
		return (memory_free(splited, command, 0), 1); */
	return (matrix_free(splited), 0);
}
