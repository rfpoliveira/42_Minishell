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
