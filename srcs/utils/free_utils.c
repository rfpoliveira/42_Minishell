/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpedrosa <rpedrosa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 16:25:52 by rpedrosa          #+#    #+#             */
/*   Updated: 2025/04/10 11:29:00 by rpedrosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"
#include "../../incs/parsing.h"

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
void	command_free(t_data **command)
{
	free(*command);
	*command = NULL;
}

void	table_free(t_simple_command **table)
{
	free(*table);
	*table = NULL;
}

//free the inoutfiles

void	inoutfiles_free(t_simple_command *table)
{
	matrix_free(table->infile);
	matrix_free(table->outfile);
	matrix_free(table->double_out);
	matrix_free(table->double_in);
}
