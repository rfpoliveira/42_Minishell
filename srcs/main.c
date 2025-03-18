/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renato-oliveira <renato-oliveira@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 15:49:26 by rpedrosa          #+#    #+#             */
/*   Updated: 2025/03/18 14:18:41 by renato-oliv      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"


/* int	signal;

void	action_handler(int numb)
{
	if (numb == SIGINT)
		signal = SIGINT;
} */

int main(void)
{
	t_command *command;
	/* struct sigaction	action; */
	char *rl;

	int i = 0;
	int j = 0;
	/* sigemptyset(&action.sa_mask);
	action.sa_handler = action_handler;
	action.sa_flags = 0;
	sigaction(SIGINT, &action_handler, NULL);
	if (signal = SIGINT)
		return (printf("sinal!")); */
	rl = readline("$> ");
	command = parsing(rl);
	if (command == NULL)
		return (1);
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
