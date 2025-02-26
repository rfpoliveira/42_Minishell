/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpedrosa <rpedrosa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 16:50:50 by rpedrosa          #+#    #+#             */
/*   Updated: 2025/02/26 17:11:15 by rpedrosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

void mount_table(t_command *command, char **splited) 
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while(i < command->number_simple_commands)
	{
		command->table[i] = malloc(sizeof(t_simple_command));
		if (!command->table[i])
		{
			memory_free(splited, command, MALLOC_ERROR);
			return ;
		}
		//split by spaces and quotes
		command->table[i]->args = parsing_split(splited[i], ' ');
		if (!(command->table[i]->args))
		{
			memory_free(splited, command, MALLOC_ERROR);
			return ;
		}
		//taking care of in and outfiles
		command->table[i]->outfile = NULL;
		command->table[i]->infile = NULL;
		while(command->table[i]->args[j])
		{
			if (command->table[i]->args[j][0] == '>' || ft_strncmp(command->table[i]->args[j], ">>", 2) == 0)
				command->table[i]->outfile = command->table[i]->args[j + 1];
			if (command->table[i]->args[j][0] == '<' || ft_strncmp(command->table[i]->args[j], "<<", 2 == 0))
				command->table[i]->infile = command->table[i]->args[j + 1];
			j++;
		}
		command->table[i]->number_args = j;
		command->table[i]->args[j] = NULL;
		j = 0;  
		i++;
	}
}

t_command *ini_command(char **splited, t_command *command)
{
	int	i;

	i = 0;
	while(splited[i])
		i++;
	command->number_simple_commands = i;
	//a simple command is anything bettewn pipes
	command->table = malloc(sizeof(t_simple_command) * i + 8);
	if (!command->table)
		return (memory_free(splited, command, MALLOC_ERROR), NULL);
	//they are stored in the table array.
	command->table[i] = NULL;
	//takes the big command and puts it in smaller bits like a table
	//if the small command has a in or outfiles it is stored in the simple_command as well
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
	//splites by pipes, making smaller blocks to handle
	splited = parsing_split(s, '|');
	if (!splited)
		return (memory_free(NULL, NULL, MALLOC_ERROR), NULL);
	//expandes variables
	handle_expanding(splited);
	if (!splited)
		return (NULL);
	//inicialize the command table with all the commands passed by the user
	command = malloc(sizeof(t_command));
	if (!command)
		return (memory_free(splited, command, MALLOC_ERROR), NULL);
	command = ini_command(splited, command);
	if (!command)
		return (NULL);
	//takes care of quotes since they are no longer needed
	handle_quotes(command);
	if (parse_commands(command) != 0)
		return (memory_free(splited, command, 0), NULL);
	while(command->table[i])
	{
		while(command->table[i]->args[j])
		{
			printf("%i: %s\n", j, command->table[i]->args[j]);
			j++;
		}
		j = 0;
		i++;
	}
	return (matrix_free(splited), command);
}
