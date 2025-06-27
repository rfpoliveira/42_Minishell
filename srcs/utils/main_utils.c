/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpedrosa <rpedrosa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 14:59:33 by rpedrosa          #+#    #+#             */
/*   Updated: 2025/06/27 15:50:51 by rpedrosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"
#include "../../incs/parsing.h"
#include "../../incs/exec.h"

/**
 @brief creates the history and frees the user inputed string
 @note string starting with whitespaces or any that cause errors
	    should not be included
*/
void	handle_history(char **user_line)
{
	int	i;

	i = 0;
	if (!*user_line || !user_line)
		return ;
	while ((*user_line)[i])
	{
		if (ft_isspace((*user_line)[i]) == 0)
		{
			add_history(*user_line);
			break ;
		}
		i++;
	}
	ft_free(user_line);
}

/**
 @brief allocs space for the main struct
		exits the program in case of error 
*/
void	alloc_struct(t_data **command)
{
	*command = malloc(sizeof(t_data));
	if (*command == NULL)
	{
		print_error(MALLOC_ERROR, 0);
		exit(1);
	}
	(*command)->table = NULL;
	(*command)->exit_code = 0;
}

/**
 @brief called to exit the program in case of EOF input by the user 
 */
void	exit_bash(char **prompt, t_data *command, int exit_code)
{
	if (prompt)
		ft_putstr_fd("exit\n", 1);
	if (exit_code <= 0)
	{
		if (command->table && *command->table)
			free_cmd(command);
		memory_free(prompt, command, exit_code);
	}
	else
	{
		if (command->table && *command->table)
			free_cmd(command);
		command->exit_code = exit_code;
		memory_free(prompt, command, 0);
	}
	exit_code = command->exit_code;
	free_envp(command);
	rl_clear_history();
	exit(exit_code);
}
