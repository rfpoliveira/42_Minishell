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
#include <fcntl.h>

char	*heredoc_file()
{
	static int	i;
	char		*filename;

	filename = ft_strjoin(".hd_temp_file", ft_itoa(i++));
	return (filename);
}

void	ft_heredoc(t_simple_command *cmd)
{
	int		fd;
	char	*file;
	char	*input;

	file = heredoc_file();
	fd = open(file, O_CREAT | O_RDWR | O_TRUNC, 0644);
	while (input && ft_strncmp(input, cmd->double_in, ft_strlen(input)))
	{

	}
}
