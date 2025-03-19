/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renato-oliveira <renato-oliveira@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 14:46:37 by renato-oliv       #+#    #+#             */
/*   Updated: 2025/03/19 14:48:22 by renato-oliv      ###   ########.fr       */
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
void free_expand(char **temp, char **prev, char **env, int flag);
void	my_getenv(char **s, char **env, int *x, int *free_flag);
int	quote_counter(char **s);

//quotes
int  handle_quotes(t_command *command);
void  delete_sigs(char *s, char A, char B);
int	count_args(t_simple_command *simple);

//redirect
int	handle_redirect(t_command *command);
void selecting_file(t_simple_command *simple, char *red, char *file);
void delete_args(t_simple_command *simple, int arg, char **buff,int flag);
void reorganize_args(t_simple_command *simple, int del, int del2);
int redirect_hopper(t_simple_command *simple, int arg, int i);
int	split_redirects(t_simple_command *simple, int arg, int i, char *red);

//splits
char	**whitespaces_split(char *s);
char	**parsing_split(char *s, char sep);
int	ft_isspace(char c);
size_t skip_quotes(char *s, size_t i);
size_t	r_count_whitespaces(char *s);
size_t	r_count_sep(char *s, char sep);

//parse_commands
int  parse_commands(t_command *command);
int parse_exit(t_simple_command *s);
int	parse_cd(t_simple_command *s);
int	parse_env(t_simple_command *s);
int parse_export_unset(t_simple_command *s);
int	check_first_pipe(char *s);
int	check_last_pipe(t_command *command);

#endif
