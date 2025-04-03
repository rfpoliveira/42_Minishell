/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpedrosa <rpedrosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 14:46:37 by renato-oliv       #+#    #+#             */
/*   Updated: 2025/04/03 16:24:19 by rpedrosa         ###   ########.fr       */
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

//expanding
int  handle_expanding(t_command *command);
void free_expand(char *temp, char *prev, char *env, int flag);
int     my_getenv(char **s, char **env, int *x, int *free_flag);
int	quote_counter(char **s, int *exit_code);
int	expande_exit_code(char **s, int *exit_code);

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
