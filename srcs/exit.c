/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpedrosa <rpedrosa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 16:35:16 by rpedrosa          #+#    #+#             */
/*   Updated: 2025/02/10 16:50:44 by rpedrosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

void print_error(int error_code)
{
	if (error_code == MALLOC_ERROR)
		printf("Error Allocating memory!\n");
	return ;
}

void  exiting_program(t_command *command, int error)
{
	int	i;
	print_error(error);
	i = 0;
	rl_clear_history();
	while (i < command->number_simple_commands && command->table[i]->args)
		matrix_free(command->table[i]->args);
	free(command->table);
	exit(0);
}
