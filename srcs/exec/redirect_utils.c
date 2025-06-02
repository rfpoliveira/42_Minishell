/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpatrici <jpatrici@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 18:33:32 by jpatrici          #+#    #+#             */
/*   Updated: 2025/06/02 21:09:12 by jpatrici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int	redir_out(char *file, t_data *data)
{
	/*if (!access(file, F_OK))*/
	/*{*/
		if (!access(file, F_OK)
		 && access(file, W_OK))
			exit(data->exit_code);
		return (open(file, O_CREAT | O_RDWR | O_TRUNC, 0644));
	/*}*/
	/*return (-1);*/
}

int	redir_double_out(char *file, t_data *data)
{
	if (!access(file, F_OK)
	&& access(file, W_OK))
		exit(data->exit_code);
	return (open(file, O_CREAT | O_RDWR | O_APPEND, 0644));
}
