/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpedrosa <rpedrosa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 16:50:50 by rpedrosa          #+#    #+#             */
/*   Updated: 2025/04/16 14:57:51 by rpedrosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"
#include "../../incs/parsing.h"

/* @brief: allocs each table (each diferent pipe) and separates each index of splited by whitespaces 
	the command will have and array of tables.
	each table will have an array of arguments that are strings.
	each table as a smaller command that was separated by pipes.
	the args are basicly each word, will have redirects, things to expand, commands each, all to be dealt with later.
	@return: frees memory in case of any errors (malloc)*/
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
/* @brief: allocs and puts the informacion in the command struct (mount_table)
	@arguments: splited is the user input line after being splited by pipe
				command is the main struct which will hold all the info 
	@return: frees the memory in case of errors (not closed quotes or malloc)*/
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
/* @brief: takes the line input by the user, parses errors and organize the data to be used in the rest of the program. 
 			check_first_pipe to check if there is a pipe in the beggining or end,
			parsing_split to split by pipes,
			ini_command for allocating most of the memory, organize each pipe in a "table",
			handle_redirect to put any redirections on the correct place in the struct,
			handle_expanding for expande everything correctly,
			handle_quotes for deleting quotes since we dont be needing them anymore.
	@notes: in case of an empy line we simply return and prompt again
	@return: 0 in case of sucess
			 1 or any number is case of error
			 IMPORTANT: to free the memory no need in any case of error */

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
	return (matrix_free(splited), 0);
}
