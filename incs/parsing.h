/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpedrosa <rpedrosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 14:46:37 by renato-oliv       #+#    #+#             */
/*   Updated: 2025/04/07 15:58:07 by rpedrosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

/*============================================================================#                               Libraries                                   #
#								libraries									  #
#============================================================================*/

#include "minishell.h"

/*============================================================================#                               Libraries                                   #
#								functions									  #
#============================================================================*/

//redirects
int	count_infiles(char **current);
int	count_outfiles(char **current);
int	count_double_outs(char **current);
int	count_double_ins(char **current);

//expanding
int  handle_expanding(t_command *command);
int	quote_counter(char **s, int *exit_code);
int	expande_exit_code(char **s, int *exit_code);
int my_get_env(char *s, char **env, int x);
char	*get_prev(char *s, int x);
int	get_str(char **s, char *prev, char *env, int len);

//quotes
int  handle_quotes(t_command *command);
int  delete_sigs(char *s, char A, char B, int *exit_code);
int	after_sig_strlen(char	*s, char A, char B);
int after_quotes_strlen(char *s);
int	count_args(t_simple_command *simple);

//splits
char	**whitespaces_split(char *s);
char	**parsing_split(char *s, char sep);
int	ft_isspace(char c);
size_t skip_quotes(char *s, size_t i);
size_t	r_count_whitespaces(char *s);
size_t	r_count_sep(char *s, char sep);

//parse_commands
int  parse_commands(t_command *command);
int parse_exit(t_simple_command *s, int *exit_code);
int	parse_cd(t_simple_command *s, int *exit_code);
int	parse_env(t_simple_command *s, int *exit_code);
int parse_export_unset(t_simple_command *s, int *exit_code);
int	check_pipes(char *s);

#endif
