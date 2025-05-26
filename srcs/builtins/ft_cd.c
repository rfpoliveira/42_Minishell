/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpatrici <jpatrici@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 19:33:53 by jpatrici          #+#    #+#             */
/*   Updated: 2025/05/20 20:46:24 by jpatrici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"
#include <fcntl.h>
#include <unistd.h>

int	ft_cd(t_simple_command *cmd)
{
	char	*dir;

	dir = getcwd(NULL, 0);
	if (!ft_strncmp(cmd->args[0], "pwd", 4))
	{
		printf("here\n");
		ft_putstr_fd(dir, 1);
		write(1, "\n", 1);
		return (1);
	}
	dir = ft_strjoin(dir, "/");
	dir = ft_strjoin(dir, cmd->args[1]);
	if (open(dir, O_DIRECTORY))
	{
		chdir(dir);
		return (1);
	}
	else 
		return (0);
}
