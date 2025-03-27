/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpatrici <jpatrici@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 17:54:10 by jpatrici          #+#    #+#             */
/*   Updated: 2025/03/21 17:58:41 by jpatrici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "minishell.h"
#include <sys/wait.h>
#include <sys/types.h>

void	ft_cmd(t_command *cmd, char **envp);
int	pipe_init(t_command *cmds, t_data *data);
int	exec_cmd(t_simple_command *cmd, char **paths, char **envp);

#endif // !EXEC_H
