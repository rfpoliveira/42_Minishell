/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpedrosa <rpedrosa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 16:35:16 by rpedrosa          #+#    #+#             */
/*   Updated: 2025/02/26 17:00:19 by rpedrosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"\

void  ft_free(void	*ptr)
{
	if (ptr)
		free(ptr);
}

//printing errors by the code passed
int print_error(int error_code)
{
	if (error_code == MALLOC_ERROR)
		return (printf("Error Allocating memory!\n"));
	else if (error_code == QUOTE_ERROR)
		return (printf("Error: non closed quotes!\n"));
	else if (error_code == COM_NOT_FOUND)
		return (printf("Error: command not found!"));
	else if (error_code == TOO_MANY_ARGS)
		return (printf("Error: Too many arguments!"));
	else if (error_code == INV_PATH)
		return (printf("Error: Invalid Path!"));
	else if (error_code == NO_ARGS)
		return (printf("Error: Missing arguments!"));
	else if (error_code == SYNTAX_ERROR)
		return (printf("Syntax Error!"));
	else if (error_code == OPEN_ERROR)
		return (printf("Error accesing path!"));
	return (0);
}

//executed whenever you need to exit the program by error or in the end, takes care of memory
void memory_free(char **s, t_command *command, int error)
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
			free(command->table[i]);
		}
		if (command->table)
			free(command->table);
		free(command);
	}
	//s is the first matrix created and NULL if command is inicialized
	if (s)
		matrix_free(s);
}
