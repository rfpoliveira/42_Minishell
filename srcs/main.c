/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpedrosa <rpedrosa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 15:49:26 by rpedrosa          #+#    #+#             */
/*   Updated: 2025/07/08 18:51:27 by rpedrosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"
#include "../incs/exec.h"

int	g_sigint_flag = 0;

static int	prompt_n_parse(char **user_line, t_data *command)
{
	command->prompt = get_prompt(command);
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
	{
		ft_putstr_fd("exit\n", 2);
		exit_bash(NULL, command, 0);
	}
	if (parsing(user_line, command) != 0)
	{
		handle_history(user_line);
		ft_free(user_line);
		return (1);
	}
	return (0);
}

static void	execution(t_data *command, char **user_line)
{
	int	fd_out;
	int	fd_in;

	fd_out = dup(STDOUT_FILENO);
	fd_in = dup(STDIN_FILENO);
	if (init_hd(command))
		ft_cmd(command);
	dup2(fd_out, STDOUT_FILENO);
	dup2(fd_in, STDIN_FILENO);
	handle_history(user_line);
	if (command->hd != NULL)
		ft_unlink_hd(command);
}

int	main(int ac, char **av, char **envp)
{
	t_data	*command;
	char	*user_line;

	if (!envp || !envp[0])
		return (ft_putstr_fd("Env not found\n", 2), 1);
	command = NULL;
	alloc_struct(&command);
	init_data(command, envp);
	while (42)
	{
		handle_signals();
		if (prompt_n_parse(&user_line, command) != 0)
			continue ;
		execution(command, &user_line);
		free_arrenvp(command);
		memory_free(NULL, command, command->exit_code);
	}
	(void) ac;
	(void) av;
}
