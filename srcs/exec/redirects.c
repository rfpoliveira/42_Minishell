/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpedrosa <rpedrosa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 19:35:02 by jpatrici          #+#    #+#             */
/*   Updated: 2025/07/08 18:33:01 by rpedrosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/exec.h"

int	outfile_redir(t_simple_command *cmd, t_data *data, int i, int b)
{
	int	fd;

	fd = -1;
	if (cmd->red_order[i] == '2')
	{
		fd = redir_out(*cmd->outfile, data, b);
		free(*cmd->outfile);
		*cmd->outfile = NULL;
		(cmd->outfile)++;
		cmd->iters->out_iter++;
	}
	else if (cmd->red_order[i] == '4')
	{
		fd = redir_double_out(*cmd->double_out, data, b);
		free(*cmd->double_out);
		*cmd->double_out = NULL;
		(cmd->double_out)++;
		cmd->iters->double_out_iter++;
	}
	else
		return (-1);
	if (fd == -1)
		return (0);
	if (fd != -1 && dup2(fd, STDOUT_FILENO) != -1)
		close(fd);
	return (1);
}

int	in_redir(t_simple_command *cmd, t_data *data, int j, int is_builtin)
{
	if (*cmd->infile && !access(*cmd->infile, F_OK | R_OK)
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
		if (!is_builtin)
			exit_bash(NULL, data, 1);
		else
			return (0);
	}
	else
		return (1);
	return (1);
}

void	exit_redirects(t_simple_command *cmd, t_data *data)
{
	if (!cmd->args[0])
		exit_bash(NULL, data, 0);
}

int	redirects(t_simple_command *cmd, t_data *data, int is_builtin)
{
	int		i;
	int		j;

	i = ft_arrlen(data->hd);
	j = -1;
	if (!cmd->double_in && !cmd->infile
		&& !cmd->outfile && !cmd->double_out)
		return (0);
	while (cmd->red_order[++j])
	{
		if (data->hd && cmd->red_order[j] == '3')
			infile_redir(data->hd[i]);
		else if (cmd->infile && *cmd->infile
			&& cmd->red_order[j] == '1')
			{
			if (!in_redir(cmd, data, j, is_builtin))
				return (-1);
			}
		else if ((cmd->outfile && *cmd->outfile && cmd->red_order[j] == '2')
			|| (cmd->double_out && *cmd->double_out
				&& cmd->red_order[j] == '4'))
			{
			if (!outfile_redir(cmd, data, j, is_builtin))
				return (-1);
			}
	}
	exit_redirects(cmd, data);
	return (j);
}
