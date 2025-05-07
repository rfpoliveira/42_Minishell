/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpatrici <jpatrici@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 19:35:02 by jpatrici          #+#    #+#             */
/*   Updated: 2025/05/06 19:35:06 by jpatrici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"
#include <fcntl.h>
#include <unistd.h>
void	redirects(t_data *data)
{
	int	i;
	int j;
	int	in_fd;
	int	out_fd;

	in_fd = -1;
	out_fd = -1;
	i = -1;
	while (data->table[++i])
	{
		j = -1;
		while (data->table[i]->infile[++j])
			if (!access(data->table[i]->infile[0], F_OK | R_OK))
				in_fd = open(data->table[i]->infile[0], O_RDONLY);
		j = -1;
		while (data->table[i]->outfile[++j])
			if (data->table[i]->outfile[0])
				out_fd = open(data->table[i]->outfile[0], O_WRONLY | O_CREAT, 0777);
		if (in_fd != -1 && dup2(in_fd, STDIN_FILENO) != -1)
			close(in_fd);
		if (out_fd != -1 && dup2(out_fd, STDOUT_FILENO) != -1)
			close(out_fd);
	}
}
