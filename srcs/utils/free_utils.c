/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpedrosa <rpedrosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 16:25:52 by rpedrosa          #+#    #+#             */
/*   Updated: 2025/04/09 16:03:25 by rpedrosa         ###   ########.fr       */
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

//free the inoutfiles

void	inoutfiles_free(t_simple_command *table)
{
	matrix_free(table->infile);
	matrix_free(table->outfile);
	matrix_free(table->double_out);
	matrix_free(table->double_in);
}
