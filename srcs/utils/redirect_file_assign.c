/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_file_assign.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpedrosa <rpedrosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 15:07:30 by rpedrosa          #+#    #+#             */
/*   Updated: 2025/04/07 17:32:06 by rpedrosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int	assign_file(char *file, t_command *command, int arg, int table)
{
	int i;

	i = 0;
	while (file[i])
		i++;
	
	file[i + 1] = NULL;
}