/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpedrosa <rpedrosa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 15:49:26 by rpedrosa          #+#    #+#             */
/*   Updated: 2025/05/14 17:25:42 by rpedrosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

int SIGINT_FLAG = 0;

int main(int ac, char **av, char **envp)
{
	t_data *command;
	char *prompt;
	char *user_line;

	command = NULL;
	alloc_struct(&command);
	int i = 0;
	int j = 0;
	int x = -1;
	handle_signals();
	prompt = get_prompt();
	if (prompt == NULL)
		{
			print_error(MALLOC_ERROR, &command->exit_code);
			exit(1);
		}
	while (42)
	{

		printf("last exit_code: %i\n", command->exit_code);
		user_line = readline(prompt);
		if (SIGINT_FLAG == 1)
		{
			SIGINT_FLAG = 0;
 			command->exit_code = 128 + 2;
		}
		if (user_line == NULL)
			exit_bash(&prompt, command);
		if (parsing(&user_line, command) != 0)
		{
			ft_free(&user_line);
			continue ;
		}
		init_data(command, envp);
		ft_cmd(command);
		while(command->table[i])
		{
			while(command->table[i]->args[j])
			{
				ft_printf("%i: %s\n", j, command->table[i]->args[j]);
				j++;
			}
			if (command->table[i]->infile)
			{
				while(command->table[i]->infile[++x])
				ft_printf("infile(%i): %s\n", x, command->table[i]->infile[x]);
			}
			x = -1;
			if (command->table[i]->outfile)
			{
				while(command->table[i]->outfile[++x])
					ft_printf("outfile(%i): %s\n", x, command->table[i]->outfile[x]);
			}
			x = -1;
			if (command->table[i]->double_in)
			{
				while(command->table[i]->double_in[++x])
					ft_printf("double_in(%i): %s\n", x, command->table[i]->double_in[x]);
			}
			x = -1;
			if (command->table[i]->double_out)
			{
				while(command->table[i]->double_out[++x])
					ft_printf("double_out(%i): %s\n", x, command->table[i]->double_out[x]);
			}
			ft_printf("order: %s\n", command->table[i]->red_order);
			x = -1;
			j = 0;
			i++;
		}
		i = 0;
		command->exit_code = 0;
		handle_history(command, &user_line);
		memory_free(NULL, command, 0);
	}
	(void) ac;
	(void) av;
}
