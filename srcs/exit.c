/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpedrosa <rpedrosa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 16:35:16 by rpedrosa          #+#    #+#             */
/*   Updated: 2025/06/25 11:19:12 by rpedrosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

/**
 @brief alters the error code in the main struct

depending of the error_code passed it alters the
exit_code with is saved in the main struct during the
whole programs 
*/
static void	handle_exit_code(int error_code, int *exit_code)
{
	if (error_code == MALLOC_ERROR)
		*exit_code = 1;
	else if (error_code == QUOTE_ERROR)
		*exit_code = 1;
	else if (error_code == COM_NOT_FOUND)
		*exit_code = 127;
	else if (error_code == TOO_MANY_ARGS)
		*exit_code = 1;
	else if (error_code == INV_PATH)
		*exit_code = 1;
	else if (error_code == NO_ARGS)
		*exit_code = 2;
	else if (error_code == SYNTAX_ERROR)
		*exit_code = 2;
	else if (error_code == OPEN_ERROR)
		*exit_code = 2;
	else if (error_code == EXIT_ERROR)
		*exit_code = 2;
	else if (error_code == STDIN_ERROR)
		*exit_code = 2;
}

/**
 @brief prints the error
 
	recieves the error code and prints the corret mensage, 
	does nothing if error_code = 0, 
	calls handle_exit_code to alter the exit_code 
*/
void	print_error(int error_code, int *exit_code)
{
	// if (error_code == MALLOC_ERROR)
	// 	ft_putstr_fd("Error Allocating memory!\n", STDERR_FILENO);
	if (error_code == QUOTE_ERROR)
		ft_putstr_fd("Non closed quotes\n", STDERR_FILENO);
	else if (error_code == COM_NOT_FOUND)
		ft_putstr_fd("command not found\n", STDERR_FILENO);
	else if (error_code == TOO_MANY_ARGS)
		ft_putstr_fd("too many arguments\n", STDERR_FILENO);
	else if (error_code == INV_PATH)
		ft_putstr_fd("Invalid Path\n", STDERR_FILENO);
	else if (error_code == NO_ARGS)
		ft_putstr_fd("Missing arguments\n", STDERR_FILENO);
	else if (error_code == SYNTAX_ERROR)
		ft_putstr_fd("Syntax Error\n", STDERR_FILENO);
	else if (error_code == OPEN_ERROR)
		ft_putstr_fd("Error accesing path\n", STDERR_FILENO);
	else if (error_code == EXIT_ERROR)
		ft_putstr_fd("numeric value needed\n", STDERR_FILENO);
	else if (error_code == STDIN_ERROR)
		ft_putstr_fd("Error reading from stdin\n", STDERR_FILENO);

	handle_exit_code(error_code, exit_code);
}

/**
 @brief free memory of the table and splited and calls print_error
 
 @note table is refering to the matrix that holds the commands and agruments
	separated by pipes.
	if command or command->table are null it does nothing.
	if splited is null it does nothing. 

 @param splited the whole user prompt separated by whitespaces
 @param command is the struct with all the data
 @param error is the error code defined in minishell.h
*/
void	memory_free(char **splited, t_data *command, int error)
{
	int	i;

	print_error(error, &command->exit_code);
	i = -1;
	if (command && command->table)
	{
		while (command->table[++i])
		{
			if (command->table[i]->args)
				matrix_free(command->table[i]->args);
			inoutfiles_free(command->table[i]);
			free(command->table[i]->red_order);
			table_free(&command->table[i]);
		}
		free(command->table);
		command->table = NULL;
	}
	if (splited)
	{
		matrix_free(splited);
		splited = NULL;
	}
}
