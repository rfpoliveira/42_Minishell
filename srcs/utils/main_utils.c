/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpedrosa <rpedrosa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 14:59:33 by rpedrosa          #+#    #+#             */
/*   Updated: 2025/04/17 11:19:10 by rpedrosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"
/* @brief: allocs space for the main struct
			exists the program in case of error */
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
/* @brief: called to exit the program in case of EOF input by the user */
void	exit_bash(char **prompt, t_data *command)
{
	ft_putstr_fd("exit\n", 1);
	ft_free(prompt);
	command_free(&command);
	rl_clear_history();
	exit(0);
}