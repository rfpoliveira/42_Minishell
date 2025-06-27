/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpedrosa <rpedrosa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 19:35:02 by jpatrici          #+#    #+#             */
/*   Updated: 2025/06/27 11:28:43 by rpedrosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

void	outfile_redir(t_simple_command *cmd, t_data *data, int i)
{
	int	fd;

	fd = -1;
	if (cmd->red_order[i] == '2')
	{
		fd = redir_out(*cmd->outfile, data);
		free(*cmd->outfile);
		*cmd->outfile = NULL;
		(cmd->outfile)++;
		cmd->iters->out_iter++;
	}
	else if (cmd->red_order[i] == '4')
	{
		fd = redir_double_out(*cmd->double_out, data);
		free(*cmd->double_out);
		*cmd->double_out = NULL;
		(cmd->double_out)++;
		cmd->iters->double_out_iter++;
	}
	else
		return ;
	if (fd != -1)
	{
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
}

void	in_redir(t_simple_command *cmd, t_data *data, int j)
{
	if (*cmd->infile &&  !access(*cmd->infile, F_OK | R_OK)
		&& cmd->red_order[j] == '1')
	{
		if (!access(*cmd->infile, F_OK | R_OK) && cmd->red_order[j] == '1')
			infile_redir(*cmd->infile);
		free(*cmd->infile);
		*cmd->infile = NULL;
		(cmd->infile)++;
		cmd->iters->in_iter++;
	}
	else if (*cmd->infile && access(*cmd->infile, F_OK | R_OK))
	{
		data->exit_code = 1;
		if (access(*cmd->infile, F_OK))
			ft_putstr_fd(" No such file or directory\n", 2);
		else if (access(*cmd->infile, R_OK))
			ft_putstr_fd(" Permission denied\n", 2);
		exit_bash(NULL, data, 1);
	}
	else
		return ;

}

int	redirects(t_simple_command *cmd, t_data *data)
{
	int		i;
	int		j;
	
	i = -1;
	j = -1;
	if (!cmd->double_in && !cmd->infile 
		&& !cmd->outfile && !cmd->double_out)
		return (0);
	while (cmd->red_order[++j])
	{
		if (data->hd && cmd->red_order[j] == '3')
			infile_redir(data->hd[++i]);
		else if (cmd->infile && *cmd->infile
				&& cmd->red_order[j] == '1')
			in_redir(cmd, data, j);
		else if ((cmd->outfile && *cmd->outfile && cmd->red_order[j] == '2')
			|| (cmd->double_out && *cmd->double_out && cmd->red_order[j] == '4'))
			outfile_redir(cmd, data, j);
	}
	return (j);
}
