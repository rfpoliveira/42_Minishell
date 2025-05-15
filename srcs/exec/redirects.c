/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpatrici <jpatrici@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 19:35:02 by jpatrici          #+#    #+#             */
/*   Updated: 2025/05/14 17:15:06 by jpatrici         ###   ########.fr       */
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
	while (cmd->outfile[++i])
	{
		if (access(cmd->outfile[i], F_OK | W_OK))
			exit(127);
		fd = open(cmd->outfile[i], O_CREAT | O_RDWR | O_TRUNC, 0644);
	}
	i = -1;
	while (cmd->double_out[++i])
	{
		if (access(cmd->double_out[i], F_OK | W_OK))
			exit(127);
		fd = open(cmd->double_out[i], O_CREAT | O_RDWR | O_APPEND, 0644);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
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

void	redirects(t_simple_command *cmd)
{
	int		i;
	char	*hd;
	
	i = -1;
	hd = NULL;
	if (!cmd->double_in && !cmd->infile 
		&& !cmd->outfile && !cmd->double_out)
		return ;
	while (cmd->double_in[++i])
		hd = ft_heredoc(cmd->double_in[i]);
	i = -1;
	while ((cmd->infile[++i] && !access(cmd->infile[i], F_OK | R_OK)) || hd)
	{
		if (hd)
		{
			infile_redir(hd);
			break ;
		}
		else if (!access(cmd->infile[i], F_OK | R_OK))
			infile_redir(cmd->infile[i]);
		if (cmd->infile[i] && access(cmd->infile[i], F_OK | R_OK))
			exit(127);
	}
	if (cmd->outfile[0] || cmd->double_out[0])
		outfile_redir(cmd);
}
