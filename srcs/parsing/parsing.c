/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renato-oliveira <renato-oliveira@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 16:50:50 by rpedrosa          #+#    #+#             */
/*   Updated: 2025/03/07 14:39:41 by renato-oliv      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/parsing.h"
#include "../../incs/minishell.h"

static void mount_table(t_command *command, char **splited) 
{
	int	i;

	i = 0;
	while(i < command->number_simple_commands)
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
		command->table[i]->outfile = NULL;
		command->table[i]->infile = NULL;
		command->table[i]->double_in = NULL;
		command->table[i]->double_out = NULL;
		i++;
	}
}

static t_command *ini_command(char **splited, t_command *command)
{
	int	i;

	i = 0;
	while(splited[i])
		i++;
	command->number_simple_commands = i;
	command->table = malloc(sizeof(t_simple_command) * i + 8);
	if (!command->table)
		return (memory_free(splited, command, MALLOC_ERROR), NULL);
	command->table[i] = NULL;
	mount_table(command, splited);
	return (command);
}

t_command *parsing(char *s)
{
	char **splited;
	t_command *command;
	int	i;
	int j;

	i = 0;
	j = 0;
	if (!s)
		return (NULL);
	if (check_first_pipe(s) == 0)
		return (memory_free(NULL, NULL, SYNTAX_ERROR), NULL);
	splited = parsing_split(s, '|');
	if (!splited)
		return (memory_free(NULL, NULL, MALLOC_ERROR), NULL);
	//handle_expanding(splited); TODO!
	if (!splited)
		return (memory_free(NULL, command, 0), NULL);
	command = malloc(sizeof(t_command));
	if (!command)
		return (memory_free(splited, command, MALLOC_ERROR), NULL);
	command = ini_command(splited, command);
	if (!command)
		return (NULL);
	if (handle_redirect(command) != 0)
		return (memory_free(splited, command, 0), NULL);
	if (handle_quotes(command) != 0)
		return (memory_free(splited, command, 0), NULL);
	if (parse_commands(command) != 0)
		return (memory_free(splited, command, 0), NULL);
	while(command->table[i])
	{
		while(command->table[i]->args[j])
		{
			printf("%i: %s\ninfile: %s\noutfile:%s\n", j, command->table[i]->args[j], command->table[i]->infile, command->table[i]->outfile);
			j++;
		}
		j = 0;
		i++;
	}
	return (matrix_free(splited), command);
}
