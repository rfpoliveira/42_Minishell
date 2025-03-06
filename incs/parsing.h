
#ifndef PARSING_H
# define PARSING_H

/*============================================================================# #                                 Libraries                                   #
#								libraries									  #
#============================================================================*/

#include "minishell.h"

void  handle_expanding(char **s);
int  handle_quotes(t_command *command);
int	parse_out_in_files(t_command *command);
void assign_redirect(t_command *command, int table_pos, int	arg_pos);

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
int	parse_pwd_env(t_simple_command *s);
int parse_export_unset(t_simple_command *s);
int	check_first_pipe(char *s);
int	check_last_pipe(t_command *command);

#endif
