/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpatrici <jpatrici@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 18:32:01 by jpatrici          #+#    #+#             */
/*   Updated: 2025/06/25 17:41:32 by jpatrici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

extern int g_sigint_flag;

void	ft_unlink_hd(t_data *data)
{
	int	i;

	i = -1;
	if (data->hd == NULL || !data->hd[0])
		return ;
	while (data->hd[++i])
	{
		if (unlink(data->hd[i]) == -1)
		{
			perror("unlink");
			exit(EXIT_FAILURE);
		}
		free(data->hd[i]);
	}
	free(data->hd);
	data->hd = NULL;
}

char	*heredoc_file()
{
	static int	i;
	char		*filename;
	char		*tmp;

	tmp = ft_itoa(i++);
	filename = ft_strjoin(".hd_temp_file_", tmp);
	free(tmp);
	return (filename);
}

char	*ft_heredoc(char *eof)
{
	int		fd;
	char	*file;
	char	*input;

	file = NULL;
	file = heredoc_file();
	fd = open(file, O_CREAT | O_RDWR | O_TRUNC, 0644);
	input = readline("> ");
	while (!g_sigint_flag && input && ft_strncmp(input, eof, ft_strlen(input)))
	{
		ft_putstr_fd(input, fd);
		write(fd, "\n", 1);
		free(input);
		input = readline("> ");
	}
	free(input);
	close(fd);
	if (g_sigint_flag)
	{
		unlink(file);
		free(file);
		return (NULL);
	}
	return (file);
}

void	signal_hd(int signumb)
{
	(void)signumb;
	ft_putstr_fd("\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	g_sigint_flag = 1;
	close(0);
}

int	init_hd(t_data *data)
{
	int	i;
	int	j;
	int count;

	i = -1;
	count = 0;
	
	if (!data->table || !data->table[0])
		return (1);
	while (data->table[++i])
	{
		j = -1;
			while (data->table[i]->double_in[++j])
				count++;
	}
	if (count != 0)
	{
		data->hd = ft_calloc(sizeof(char *), count + 1);
		data->hd[count] = NULL;
		i = -1;
		j = -1;
		count = 0;
		signal(SIGINT, &signal_hd);
		while (data->table[++i])
		{
			j = -1;
			while (data->table[i]->double_in[++j])
			{
				data->hd[count] = ft_heredoc(data->table[i]->double_in[j]);
				if (!data->hd[count++])
					return (0);
			}
		}
	}
	/*handle_signals();*/
	return (1);
}
