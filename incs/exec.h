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

int		ft_cmd(t_data *data);
void	fd_handler(t_data *data, pid_t *pid);
int		pipe_handle(t_data *data, int *fd, int index);
int		pipe_init(t_data *data, int index);
int		exec_cmd(t_simple_command *cmd, t_data *data);
char	**pathfind(t_env *envp);
t_env	*env_new(char *envp);
char	**envp_cpy(t_env *envp);
void	env_addback(t_env *env, t_env *node);
void 	init_envp(t_env **env, char **envp);
void	init_data(t_data *data, char **envp);
void	redirects(t_simple_command *cmd);
char	*ft_heredoc(char *eof);

#endif // !EXEC_H
