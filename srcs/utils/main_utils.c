/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpedrosa <rpedrosa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 14:59:33 by rpedrosa          #+#    #+#             */
/*   Updated: 2025/06/09 17:00:18 by rpedrosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"
#include "../../incs/parsing.h"

/**
 @brief creates the history and frees the user inputed string
 @note string starting with whitespaces or any that cause errors
	    should not be included
*/
void	handle_history(t_data *command, char **user_line)
{
	if (!*user_line || !user_line)
		return ;
	if (command->exit_code != 0)
		return (ft_free(user_line));
	if (ft_isspace((*user_line)[0]) == 0)
		add_history(*user_line);
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
void	exit_bash(char **prompt, t_data *command)
{
	ft_putstr_fd("exit\n", 1);
	ft_free(prompt);
	command_free(&command);
	rl_clear_history();
	exit(0);
}
