/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpedrosa <rpedrosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 16:25:52 by rpedrosa          #+#    #+#             */
/*   Updated: 2025/04/03 17:06:48 by rpedrosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

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

//free the inoutfiles

void	inoutfiles_free(char **file)
{
	int i;

	i = -1;
	while(file[i])
		ft_free(&file[i]);
	free(file);
}
