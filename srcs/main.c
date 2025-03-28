/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpedrosa <rpedrosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 15:49:26 by rpedrosa          #+#    #+#             */
/*   Updated: 2025/03/28 16:18:36 by rpedrosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

int main(void)
{
	t_command *command;
	char *prompt;
	char *rl;

	command = NULL;
	alloc_struct(&command);
	int i = 0;
	int j = 0;
	handle_signals();
	while (42)
	{
		prompt = get_prompt();
		if (prompt == NULL)
		{
			print_error(MALLOC_ERROR, &command->exit_code);
			continue ;
		}
		rl = readline(prompt);
		if (rl == NULL)
			exit_bash(&prompt, command);
		add_history(rl);
		parsing(rl, command);
		if (command->table == NULL)
		{
			ft_free(&rl);
			ft_free(&prompt);
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
		printf("exit_code: %i\n", command->exit_code);
		memory_free(&command->exit_code, NULL, command, 0);
		ft_free(&prompt);
	}
}
