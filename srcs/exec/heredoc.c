/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpatrici <jpatrici@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 18:32:01 by jpatrici          #+#    #+#             */
/*   Updated: 2025/05/13 18:32:06 by jpatrici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

extern int SIGINT_FLAG;

void	ft_unlink_hd(t_data *data)
{
	int	i;

	i = -1;
	if (data->hd == NULL)
		return ;
	while (data->hd[++i])
	{
		if (unlink(data->hd[i]) == -1)
		{
			perror("unlink");
			exit(EXIT_FAILURE);
		}
		free(data->hd[i]);
		data->hd[i] = NULL;
	}
}

char	*heredoc_file()
{
	static int	i;
	char		*filename;

	filename = ft_strjoin(".hd_temp_file_", ft_itoa(i++));
	return (filename);
}

char	*ft_heredoc(char *eof)
{
	int		fd;
	static char	*file;
	char	*input;

	if (file)
		free(file);
	file = heredoc_file();
	fd = open(file, O_CREAT | O_RDWR | O_TRUNC, 0644);
	input = readline("> ");
	while (input && ft_strncmp(input, eof, ft_strlen(input)))
	{
		ft_putstr_fd(input, fd);
		write(fd, "\n", 1);
		free(input);
		input = readline("> ");
	}
	free(input);
	close(fd);
	return (file);
}
void	init_hd(t_data *data)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	while (data->table[++i])
		while (data->table[i]->double_in[j])
			j++;
	if (j != 0)
	{
		data->hd = ft_calloc(sizeof(char *), j + 1);
		data->hd[j] = NULL;
		i = -1;
		j = -1;
		while (data->table[++i])
			while (data->table[i]->double_in[++j])
				data->hd[j] = ft_heredoc(data->table[i]->double_in[j]);
	}
}
