/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpedrosa <rpedrosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 16:35:16 by rpedrosa          #+#    #+#             */
/*   Updated: 2025/03/11 12:33:26 by rpedrosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"\

void  ft_free(char	**ptr)
{
	if (*ptr != NULL)
	{
		free(*ptr);
		*ptr = NULL;
	}
}

//printing errors by the code passed
void print_error(int error_code)
{
	if (error_code == MALLOC_ERROR)
		ft_putstr_fd("Error Allocating memory!\n", STDERR_FILENO);
	else if (error_code == QUOTE_ERROR)
		ft_putstr_fd("Error: non closed quotes!\n", STDERR_FILENO);
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
}

//executed whenever you need to exit the program by error or in the end, takes care of memory
void memory_free(char **splited, t_command *command, int error)
{
	int	i;

	print_error(error);
	//rl_clear_history();
	i = -1;
	//command is null is error is before it is inicialized
	if (command)
	{
		while (command->table[++i])
		{
			matrix_free(command->table[i]->args);
			ft_free(&command->table[i]->outfile);
			ft_free(&command->table[i]->infile);
			ft_free(&command->table[i]->double_out);
			ft_free(&command->table[i]->double_in);
			free(command->table[i]);
		}
		if (command->table)
			free(command->table);
		free(command);
	}
	//s is the first matrix created and NULL if command is inicialized
	if (splited)
	{
		matrix_free(splited);
		splited = NULL;
	}
}
