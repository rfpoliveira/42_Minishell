/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renato-oliveira <renato-oliveira@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 16:50:50 by rpedrosa          #+#    #+#             */
/*   Updated: 2025/03/14 16:33:23 by renato-oliv      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/parsing.h"
#include "../../incs/minishell.h"

//puts everything separated by pipes and spaces ready to be parsed
static void	mount_table(t_command *command, char **splited)
{
	int	i;

	i = 0;
	while (i < command->number_simple_commands)
	{
		command->table[i] = malloc(sizeof(t_simple_command));
		if (!command->table[i])
		{
			memory_free(splited, command, MALLOC_ERROR);
			return ;
		}
		command->table[i]->args = whitespaces_split(splited[i]);
		if (!(command->table[i]->args))
		{
			memory_free(splited, command, MALLOC_ERROR);
			return ;
		}
		command->table[i]->number_args = count_args(command->table[i]);
		command->table[i]->outfile = NULL;
		command->table[i]->infile = NULL;
		command->table[i]->double_in = NULL;
		command->table[i]->double_out = NULL;
		i++;
	}
}
//inicializacion of the main structure
static void	ini_command(char **splited, t_command *command)
{
	int	i;

	i = 0;
	while (splited[i])
		i++;
	command->number_simple_commands = i;
	command->table = malloc(sizeof(t_simple_command) * i + 8);
	if (!command->table)
		return (memory_free(splited, command, MALLOC_ERROR));
	command->table[i] = NULL;
	if (quote_counter(splited) != 0)
		return (memory_free(splited, command, 0));
	mount_table(command, splited);
}
//calls everything in the following order:
/* check_first_pipe to check if there is a pipe in the beggining
parsing_split to split by pipes 
ini_command for allocating most of the memory and inicializing the main struct
handle_redirect to put any redirections on the correct place in the strcut 
handle_expanding for expande everything correctly
handle_quotes for deleting quotes since we dont be needing them anymore
and parse command to check if the commands exist or not
if any of this returns any error the programs stops and calls memory free */

t_command	*parsing(char *s)
{
	char		**splited;
	t_command	*command;

	if (!s)
		return (NULL);
	if (check_first_pipe(s) == 0)
		return (memory_free(NULL, NULL, SYNTAX_ERROR), NULL);
	splited = parsing_split(s, '|');
	if (!splited)
		return (memory_free(NULL, NULL, MALLOC_ERROR), NULL);
	command = malloc(sizeof(t_command));
	if (!command)
		return (memory_free(splited, NULL, MALLOC_ERROR), NULL);
	ini_command(splited, command);
	if (!command)
		return (NULL);
	if (handle_redirect(command) != 0)
		return (memory_free(splited, command, 0), NULL);
	if (handle_expanding(command) != 0)
		return (memory_free(splited, command, 0), NULL);
	if (handle_quotes(command) != 0)
		return (memory_free(splited, command, 0), NULL);
	if (parse_commands(command) != 0)
		return (memory_free(splited, command, 0), NULL);
	return (matrix_free(splited), command);
}
