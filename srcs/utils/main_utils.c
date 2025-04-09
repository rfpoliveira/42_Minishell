/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpedrosa <rpedrosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 14:59:33 by rpedrosa          #+#    #+#             */
/*   Updated: 2025/04/09 15:53:11 by rpedrosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void alloc_struct(t_data **command)
{
	*command = malloc(sizeof(t_data));
	if (*command == NULL)
	{
		print_error(MALLOC_ERROR, 0);
		exit(1);
	}
	(*command)->exit_code = 0;	
}

void	exit_bash(char **prompt, t_data *command)
{
	ft_putstr_fd("exit\n", 1);
	ft_free(prompt);
	command_free(&command);
	rl_clear_history();
	exit(0);
}