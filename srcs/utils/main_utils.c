/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpedrosa <rpedrosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 14:59:33 by rpedrosa          #+#    #+#             */
/*   Updated: 2025/03/27 16:12:23 by rpedrosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void alloc_struct(t_command **command)
{
	*command = malloc(sizeof(t_command));
	if (*command == NULL)
	{
		print_error(MALLOC_ERROR, 0);
		exit(1);
	}
	(*command)->exit_code = 0;	
}

void	exit_bash(char **prompt, t_command *command)
{
	printf("exit\n");
	ft_free(prompt);
	memory_free(&command->exit_code, NULL, command, 0);
	command_free(&command);
	rl_clear_history();
	exit(0);
}