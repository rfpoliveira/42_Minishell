/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpatrici <jpatrici@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 18:33:32 by jpatrici          #+#    #+#             */
/*   Updated: 2025/06/04 15:18:45 by jpatrici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int	redir_out(char *file, t_data *data)
{
	if (!access(file, F_OK)
	 && access(file, W_OK))
		exit(data->exit_code);
	return (open(file, O_CREAT | O_RDWR | O_TRUNC, 0644));
}

int	redir_double_out(char *file, t_data *data)
{
	if (!access(file, F_OK)
	&& access(file, W_OK))
		exit(data->exit_code);
	return (open(file, O_CREAT | O_RDWR | O_APPEND, 0644));
}

void	infile_redir(char *infile)
{
	int	fd;

	fd = -1;
	if (infile)
		fd = open(infile, O_RDONLY);
	if (dup2(fd, STDIN_FILENO) == -1)
		return ;
	close(fd);
}
