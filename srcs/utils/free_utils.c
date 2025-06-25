/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpedrosa <rpedrosa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 16:25:52 by rpedrosa          #+#    #+#             */
/*   Updated: 2025/06/25 15:44:13 by rpedrosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"
#include "../../incs/parsing.h"

/** 
 @brief checks if a pointer exists, frees and sets to NULL if so 
*/
void	ft_free(char **ptr)
{
	if (*ptr != NULL && ptr != NULL)
	{
		free(*ptr);
		*ptr = NULL;
	}
}

/** 
 @brief free the command and sets the pointer to null
*/
void	command_free(t_data **command)
{
	free(*command);
	*command = NULL;
}

/** 
 @brief free the table and sets the pointer to null 
 */
void	table_free(t_simple_command **table)
{
	free(*table);
	*table = NULL;
}

/**
 @brief frees all the matrinx of saved files
*/
void	inoutfiles_free(t_simple_command *table)
{
	if (table->infile)
	{
		if (*table->infile == NULL && table->numb_ins > 0)
			table->infile -= table->numb_ins;
		matrix_free(table->infile);
	}
	if (table->outfile)
	{
		if (*table->outfile == NULL && table->numb_outs > 0)
			table->outfile -= table->numb_outs;
		matrix_free(table->outfile);
	}
	if (table->double_out)
	{
		if (*table->double_out == NULL && table->numb_double_outs > 0)
			table->double_out -= table->numb_double_outs;
		matrix_free(table->double_out);
	}
	if (table->double_in)
		matrix_free(table->double_in);
}
