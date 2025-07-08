/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpedrosa <rpedrosa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 14:46:37 by renato-oliv       #+#    #+#             */
/*   Updated: 2025/07/08 18:49:22 by rpedrosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

/*============================================================================#
#								libraries									  #
#============================================================================*/

# include "minishell.h"

/*============================================================================#
#								functions									  #
#============================================================================*/

//redirects
int		handle_redirect(t_data *command, int i, int j);
int		count_infiles(char **current);
int		count_outfiles(char **current);
int		count_double_outs(char **current);
int		count_double_ins(char **current);
int		assign_file(t_data *command, int table, int arg, int chr);
int		assign_util_double_in(t_data *command, int arg, int table, int chr);
int		assign_util_double_out(t_data *command, int arg, int table, int chr);
int		assign_util_outfile(t_data *command, int arg, int table, int chr);
int		assign_util_infile(t_data *command, int arg, int table, int chr);
int		new_arg_counter(t_simple_command *table, char **args);
int		populate_tmp(char **tmp, t_data *com, char **cur, int i);
int		alloc_file(t_data *command, int curr_table);
char	*copy_red(char *str);
void	iter(char c, int *chr);

//expanding
int		handle_expanding(t_data *command);
int		quote_counter(char **s, int *exit_code);
int		expande_exit_code(char **env, int *exit_code);
int		my_get_env(char *s, char **env, int x, t_data *data);
char	*get_prev(char *s, int x);
int		get_str(char **s, char *prev, char *env, int len);
int		mid_expand_quote_handler(int *flag, int *i, char *current);
int		sep_per_words(t_simple_command *curr_table, int *exit_code);
int	handle_tilde(t_data *command);

//quotes
int		handle_quotes(t_data *command);
int		after_quotes_strlen(char **s);
int		count_args(t_simple_command *simple);

//splits
char	**whitespaces_split(char *s);
char	**parsing_split(char *s, char sep);
int		ft_isspace(char c);
size_t	skip_quotes(char *s, size_t i);
size_t	r_count_whitespaces(char *s);
size_t	r_count_sep(char *s, char sep);

void	red_order_code(int count, char *command, t_simple_command *table);
int		check_pipes(char *s);
void	count_everything(t_data *command, int i);

int		handle_empty_args(t_data *command);

#endif
