/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpatrici <jpatrici@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 17:54:10 by jpatrici          #+#    #+#             */
/*   Updated: 2025/06/25 20:49:46 by jpatrici         ###   ########.fr       */
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
int		exec_cmd(t_simple_command *cmd, t_data *data, pid_t *pid);
int		setpaths(t_simple_command *cmd, char **paths);
char	**pathfind(t_env *envp);
char	*ft_strjoin_free(char *s1, char *join);
void	free_arrenvp(t_data *data);
t_env	*env_new(char *envp);
char	**envp_cpy(t_env *envp);
void	env_addback(t_env *env, t_env *node);
void 	init_envp(t_env **env, char **envp);
void	init_data(t_data *data, char **envp);
int		redirects(t_simple_command *cmd, t_data *data);
int		redir_out(char *file, t_data *data);
int		redir_double_out(char *file, t_data *data);
void	infile_redir(char *infile);
char	*ft_heredoc(char *eof);
void	init_hd(t_data *data);
int		ft_echo(t_simple_command *cmd);
int		ft_cd(t_data *data, t_simple_command *cmd);
int		ft_strchrlen(char *s, char c);
int		ft_export(t_simple_command *cmd, t_data *data);
int		ft_add_key(t_env **env, char *args, int keysep);
int		swap_util(t_env **exp, t_env *temp);
int		export_parse(char *args, int keysep);
int		export_error(char *error);
int		add_to_export(t_env **env, char *args, int keysep);
int		env_len(t_env *env);
int		ft_env(t_data *data);
int		ft_unset(t_simple_command *cmd, t_data *data);
int	    ft_exit(t_simple_command *cmd, t_data *data);
void	ft_unlink_hd(t_data *data);
void	free_envp(t_data *data);
void	free_cmd(t_data *data);
void	dir_check(t_data *data, t_simple_command *cmd);

#endif // !EXEC_H
