/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpedrosa <rpedrosa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 16:35:16 by rpedrosa          #+#    #+#             */
/*   Updated: 2025/02/20 15:52:03 by rpedrosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"\

void  ft_free(void	*ptr)
{
	if (ptr)
		free(ptr);
}

//printing errors by the code passed
void print_error(int error_code)
{
	if (error_code == MALLOC_ERROR)
		printf("Error Allocating memory!\n");
	else if (error_code == QUOTE_ERROR)
		printf("Syntax error: non closed quotes!\n");
	return ;
}

//executed whenever you need to exit the program by error or in the end, takes care of memory
void  exiting_program(char **s, t_command *command, int error)
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
	exit(error);
}
