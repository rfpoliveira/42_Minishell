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

void	outfile_redir(t_simple_command *cmd)
{
	int	i;
	int	fd;

	i = -1;
	if (cmd->outfile)
		while (cmd->outfile[++i])
			fd = open(cmd->outfile[i], O_CREAT | O_RDWR | O_TRUNC, 0644);
	i = -1;
	if (cmd->double_out)
		while (cmd->double_out[++i])
			fd = open(cmd->double_out[i], O_CREAT | O_RDWR | O_APPEND, 0644);
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

void	infile_redir(char *infile)
{
	int	fd;

	fd = open(infile, O_RDONLY);
	if (dup2(fd, STDIN_FILENO) == -1)
		return ;
	close(fd);
}

void	redirects(t_simple_command *cmd)
{
	int	i;

	i = -1;
	while (cmd->infile[++i])
		if (access(cmd->infile[i], F_OK | R_OK))
			infile_redir(cmd->infile[i]);
	i = -1;
	while (cmd->outfile[++i])
		outfile_redir(cmd);
		/*while (data->table[i]->double_in)*/
		/*	ft_heredoc(data->table[i]->double_in);*/
}
