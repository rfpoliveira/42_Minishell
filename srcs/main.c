/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpedrosa <rpedrosa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 15:49:26 by rpedrosa          #+#    #+#             */
/*   Updated: 2025/03/25 17:40:02 by rpedrosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

int main(void)
{
	t_command *command;
	char *prompt;
	char *rl;
	int		exit_code;

	int i = 0;
	int j = 0;
	exit_code = 0;
	handle_signals();
	prompt = get_prompt();
	if (prompt == NULL)
		memory_free(&exit_code, NULL, NULL, MALLOC_ERROR);
	while (42)
	{
		rl = readline(prompt);
		if (rl == NULL)
		{
			printf("exit\n");
			ft_free(&prompt);
			rl_clear_history();
			exit(0);
		}
		add_history(rl);
		command = parsing(rl, &exit_code);
		if (command == NULL)
		{
			ft_free(&rl);
			continue ;
		}
		while(command->table[i])
		{
			while(command->table[i]->args[j])
			{
				printf("%i: %s\n", j, command->table[i]->args[j]);
				j++;
			}
			printf("infile: %s\noutfile: %s\n", command->table[i]->infile, command->table[i]->outfile);
			printf("double_in: %s\ndouble_out: %s\n", command->table[i]->double_in, command->table[i]->double_out);
			j = 0;
			i++;
		}
		i = 0;
		printf("exit_code: %i\n", exit_code);
		memory_free(&exit_code, NULL, command, 0);
	}
	ft_free(&prompt);
}
