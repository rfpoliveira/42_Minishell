
#ifndef PARSING_H
# define PARSING_H

/*============================================================================# #                                 Libraries                                   #
#								libraries									  #
#============================================================================*/

#include "minishell.h"

char	**whitespaces_split(const char *s);
void  handle_expanding(char **s);
int  handle_quotes(t_command *command);
int	parse_out_in_files(t_command *command);
size_t skip_quotes(const char *s, size_t i);
void assign_redirect(t_command *command, int table_pos, int	arg_pos);
int	ft_isspace(char c);


//parse_commands
int  parse_commands(t_command *command);
int parse_exit(t_simple_command *s);
int	parse_cd(t_simple_command *s);
int	parse_pwd_env(t_simple_command *s);
int parse_export_unset(t_simple_command *s);

#endif
