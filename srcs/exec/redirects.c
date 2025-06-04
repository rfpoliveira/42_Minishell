/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpatrici <jpatrici@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 19:35:02 by jpatrici          #+#    #+#             */
/*   Updated: 2025/06/04 17:01:21 by jpatrici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"
#include <fcntl.h>
#include <unistd.h>

void	outfile_redir(t_simple_command *cmd, t_data *data, int i)
{
	/*int	i;*/
	int	j;
	int	fd;
	int	n;

	/*i = -1;*/
	fd = -1;
	j = -1;
	n = -1;
	/*while (cmd->red_order[++i])*/
	/*{*/
		if (cmd->outfile[j + 1] && cmd->red_order[i] == '2' && (++j || !j))
			fd = redir_out(cmd->outfile[j], data);
		else if (cmd->double_out[n + 1] && cmd->red_order[i] == '4' && (++n || !n))
			fd = redir_double_out(cmd->double_out[n], data);
		else
			return ;
	/*}*/
	if (fd != -1)
	{
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
}

void	in_redir(t_simple_command *cmd, int j)
{
	int	i;
	/*int	j;*/

	/*i = -1;*/
	/*j = -1;*/
	/*while (cmd->red_order[++j])*/
	/*{*/
		if ((cmd->infile[i + 1] && !access(cmd->infile[i + 1], F_OK | R_OK)
			&& cmd->red_order[j] == '1' && (++i || !i)))
		{
			if (!access(cmd->infile[i], F_OK | R_OK) && cmd->red_order[j] == '1')
				infile_redir(cmd->infile[i]);
			if (cmd->infile[i] && access(cmd->infile[i], F_OK | R_OK))
				exit(127);
		}
		else
			return ;
	/*}*/

}

void	redirects(t_simple_command *cmd, t_data *data)
{
	/*int		i;*/
	int		j;
	
	j = -1;
	if (!cmd->double_in && !cmd->infile 
		&& !cmd->outfile && !cmd->double_out)
		return ;
	while (cmd->red_order[++j])
	{
		if (data->hd && cmd->red_order[j] == '3')
		{
			infile_redir(data->hd);
			/*break ;*/
		}
		if (cmd->infile && cmd->red_order[j] == '1')
			in_redir(cmd, j);
		if (cmd->outfile && cmd->red_order[j] == '2')
			outfile_redir(cmd, data, j);
	}
}
