/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpedrosa <rpedrosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 16:35:16 by rpedrosa          #+#    #+#             */
/*   Updated: 2025/03/27 16:44:58 by rpedrosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"\

//free that check if the pointer exists
void	ft_free(char **ptr)
{
	if (*ptr != NULL)
	{
		free(*ptr);
		*ptr = NULL;
	}
}
//free the command and sets the pointer to null
void	command_free(t_command **command)
{
	free(*command);
	*command = NULL;
}

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

//printing errors to the standard error by the code passed
void	print_error(int error_code, int *exit_code)
{
	if (error_code == MALLOC_ERROR)
		ft_putstr_fd("Error Allocating memory!\n", STDERR_FILENO);
	else if (error_code == QUOTE_ERROR)
		ft_putstr_fd("Error: Non closed quotes!\n", STDERR_FILENO);
	else if (error_code == COM_NOT_FOUND)
		ft_putstr_fd("Error: command not found!\n", STDERR_FILENO);
	else if (error_code == TOO_MANY_ARGS)
		ft_putstr_fd("Error: Too many arguments!\n", STDERR_FILENO);
	else if (error_code == INV_PATH)
		ft_putstr_fd("Error: Invalid Path!\n", STDERR_FILENO);
	else if (error_code == NO_ARGS)
		ft_putstr_fd("Error: Missing arguments!\n", STDERR_FILENO);
	else if (error_code == SYNTAX_ERROR)
		ft_putstr_fd("Syntax Error!\n", STDERR_FILENO);
	else if (error_code == OPEN_ERROR)
		ft_putstr_fd("Error accesing path!\n", STDERR_FILENO);
	else if (error_code == EXIT_ERROR)
		ft_putstr_fd("Error: numeric value needed!\n", STDERR_FILENO);
	else if (error_code == STDIN_ERROR)
		ft_putstr_fd("Error reading from stdin!\n", STDERR_FILENO);
	handle_exit_code(error_code, exit_code);
}

//executed whenever you need to exit the program by 
//error or in the end, takes care of memory
void	memory_free(int *exit_code, char **splited, t_command *command, int error)
{
	int	i;

	print_error(error, exit_code);
	i = -1;
	if (command->table)
	{
		while (command->table[++i])
		{
			if (command->table[i]->args)
				matrix_free(command->table[i]->args);
			ft_free(&command->table[i]->outfile);
			ft_free(&command->table[i]->infile);
			ft_free(&command->table[i]->double_out);
			ft_free(&command->table[i]->double_in);
			free(command->table[i]);
		}
		if (command->table)
			free(command->table);
	}
	if (splited)
	{
		matrix_free(splited);
		splited = NULL;
	}
}
