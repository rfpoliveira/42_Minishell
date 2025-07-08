/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpedrosa <rpedrosa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 18:33:32 by jpatrici          #+#    #+#             */
/*   Updated: 2025/07/08 18:31:22 by rpedrosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/exec.h"

int	redir_out(char *file, t_data *data, int b)
{
	if (!access(file, F_OK)
		&& access(file, W_OK))
	{
		ft_putstr_fd(" Permission denied\n", 2);
		if (!b)
			exit_bash(NULL, data, 1);
	}
	return (open(file, O_CREAT | O_RDWR | O_TRUNC, 0644));
}

int	redir_double_out(char *file, t_data *data, int b)
{
	if (!access(file, F_OK)
		&& access(file, W_OK))
	{
		ft_putstr_fd(" Permission denied\n", 2);
		if (!b)
			exit_bash(NULL, data, 1);
	}
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

int	ft_arrlen(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return (0);
	while (arr[i])
		i++;
	return (i - 1);
}
