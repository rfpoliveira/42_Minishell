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
	fd = -1;
	if (cmd->outfile)
		while (cmd->outfile[++i])
			fd = open(cmd->outfile[i], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (cmd->double_out)
	{
		i = -1;
		while (cmd->double_out[++i])
			fd = open(cmd->double_out[i], O_CREAT | O_RDWR | O_APPEND, 0644);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

void	infile_redir(t_simple_command *cmd)
{
	int	fd;
	int	i;

	i = -1;
	fd = -1;
	if (cmd->infile)
		while (cmd->infile[++i])
			fd = open(cmd->infile[i], O_RDONLY);
	if (dup2(fd, STDIN_FILENO) == -1)
		return ;
	close(fd);
}

void	redirects(t_simple_command *cmd)
{
	/*if (cmd->double_in)*/
	/*	ft_heredoc(cmd);*/
	if (!access(cmd->infile[0], F_OK | R_OK))
			infile_redir(cmd);
	else if (cmd->infile && access(cmd->infile[0], F_OK | R_OK))
		exit(127);
	if (cmd->outfile || cmd->double_out)
		outfile_redir(cmd);
		/*while (data->table[i]->double_in)*/
		/*	ft_heredoc(data->table[i]->double_in);*/
}
