/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renato-oliveira <renato-oliveira@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 15:49:26 by rpedrosa          #+#    #+#             */
/*   Updated: 2025/03/19 17:13:37 by renato-oliv      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"
#include "../incs/signals.h"

pid_t	current_pid = 0;

int main(void)
{
	t_command *command;
	char *rl;

	int i = 0;
	int j = 0;
	handle_signals();
	while (42)
	{
		rl = readline("Minishell do Aço: ");
		if (rl == NULL)
		{
			printf("exit\n");
			rl_clear_history();
			exit(0);
		}
		add_history(rl);
		command = parsing(rl);
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
		memory_free(NULL, command, 0);
	}
}
