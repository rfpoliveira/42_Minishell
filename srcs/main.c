/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpedrosa <rpedrosa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 15:49:26 by rpedrosa          #+#    #+#             */
/*   Updated: 2025/06/27 13:30:51 by rpedrosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"
#include <fcntl.h>
#include <unistd.h>

int g_sigint_flag = 0;

static int prompt_n_parse(char **user_line, t_data *command)
{
	command->prompt = get_prompt();
	if (command->prompt == NULL)
	{
		print_error(MALLOC_ERROR, &command->exit_code);
		exit(1);
	}
	*user_line = readline(command->prompt);
	ft_free(&command->prompt);
	if (g_sigint_flag == 1)
	{
		g_sigint_flag = 0;
		command->exit_code = 128 + 2;
	}
	if (*user_line == NULL)
		exit_bash(NULL, command, 0);
	if (parsing(user_line, command) != 0)
	{
		ft_free(user_line);
		return (1);
	}
	return (0);
}

static void execution (t_data *command, char **user_line)
{
	if (command->table[0]->double_in)
		init_hd(command);
	int	fd_out = dup(STDOUT_FILENO);
	int	fd_in = dup(STDIN_FILENO);
	ft_cmd(command);
	dup2(fd_out, STDOUT_FILENO);
	dup2(fd_in, STDIN_FILENO);
	handle_history(user_line);
	if (command->hd != NULL)
		ft_unlink_hd(command);
	
}

int main(int ac, char **av, char **envp)
{
	t_data *command;
	char *user_line;

	command = NULL;
	alloc_struct(&command);
	init_data(command, envp);
	handle_signals();
	while (42)
	{
		if (prompt_n_parse(&user_line, command) != 0)
			continue ;
/* 		for (int i = 0; command->table[0]->args[i]; i++)
			dprintf(2, "token arg: %s\n", command->table[0]->args[i]); */
		execution(command, &user_line);
		free_arrenvp(command);
		memory_free(NULL, command, command->exit_code);
	}
	(void) ac;
	(void) av;
}
