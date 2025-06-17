/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpedrosa <rpedrosa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 15:49:26 by rpedrosa          #+#    #+#             */
/*   Updated: 2025/06/17 18:02:08 by rpedrosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"
#include <unistd.h>

int g_sigint_flag = 0;

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
		command->prompt = get_prompt();
		if (command->prompt == NULL)
		{
			print_error(MALLOC_ERROR, &command->exit_code);
			exit(1);
		}
		user_line = readline(command->prompt);
		ft_free(&command->prompt);
		if (g_sigint_flag == 1)
		{
			g_sigint_flag = 0;
 			command->exit_code = 128 + 2;
		}
		if (user_line == NULL)
			exit_bash(NULL, command);
		if (parsing(&user_line, command) != 0)
		{
			ft_free(&user_line);
			continue ;
		}
		if (command->table[0]->double_in)
			init_hd(command);
		int	fd_out = dup(STDOUT_FILENO);
		int	fd_in = dup(STDIN_FILENO);
		ft_cmd(command);
		dup2(fd_out, STDOUT_FILENO);
		dup2(fd_in, STDIN_FILENO);
		command->exit_code = 0;
		handle_history(&user_line);
		if (command->hd != NULL)
			ft_unlink_hd(command);
		free_arrenvp(command);
		memory_free(NULL, command, 0);
	}
	(void) ac;
	(void) av;
}
