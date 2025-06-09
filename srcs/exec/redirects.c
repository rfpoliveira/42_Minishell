/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpatrici <jpatrici@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 19:35:02 by jpatrici          #+#    #+#             */
/*   Updated: 2025/06/04 17:15:31 by jpatrici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"
#include <fcntl.h>
#include <unistd.h>

void	outfile_redir(t_simple_command *cmd, t_data *data, int i)
{
	int	fd;

	fd = -1;
	if (cmd->red_order[i] == '2')
	{
		fd = redir_out(*cmd->outfile, data);
		(cmd->outfile)++;
	}
	else if (cmd->red_order[i] == '4')
	{
		fd = redir_double_out(*cmd->double_out, data);
		(cmd->double_out)++;
	}
	else
		return ;
	if (fd != -1)
	{
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
}

void	in_redir(t_simple_command *cmd, int j)
{
	if (*cmd->infile && !access(*cmd->infile, F_OK | R_OK)
		&& cmd->red_order[j] == '1')
	{
		if (!access(*cmd->infile, F_OK | R_OK) && cmd->red_order[j] == '1')
			infile_redir(*cmd->infile);
		(cmd->infile)++;
	}
	else if (*cmd->infile && access(*cmd->infile, F_OK | R_OK))
		exit(127);
	else
		return ;

}

void	redirects(t_simple_command *cmd, t_data *data)
{
	int		i;
	int		j;
	
	i = -1;
	j = -1;
	if (!cmd->double_in && !cmd->infile 
		&& !cmd->outfile && !cmd->double_out)
		return ;
	while (cmd->red_order[++j])
	{
		if (data->hd && cmd->red_order[j] == '3')
			infile_redir(data->hd[++i]);
		else if (*cmd->infile && cmd->red_order[j] == '1')
			in_redir(cmd, j);
		else if ((*cmd->outfile && cmd->red_order[j] == '2')
			|| (*cmd->double_out && cmd->red_order[j] == '4'))
			outfile_redir(cmd, data, j);
	}
}
