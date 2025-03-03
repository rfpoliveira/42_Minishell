
#ifndef MINISHELL_H
# define MINISHELL_H

/*============================================================================# #                                 Libraries                                   #
#								libraries									  #
#============================================================================*/

#include "../libft/libft.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <curses.h>
#include <term.h>
#include <errno.h>

/*============================================================================#
#								  ERRORS									  #
#============================================================================*/

#define MALLOC_ERROR 1
#define QUOTE_ERROR -1
#define COM_NOT_FOUND -2
#define	TOO_MANY_ARGS -3
#define INV_PATH -4
#define NO_ARGS -5
#define	SYNTAX_ERROR -6
#define OPEN_ERROR -7
/*============================================================================#
#								 STRUCTS									  #
#============================================================================*/

typedef struct s_simple_command
{
	int	number_args;
	char **args;
	char *infile;
	char *outfile;
}	t_simple_command;

typedef struct s_command
{
	int number_simple_commands;
	t_simple_command  **table;
}	t_command;

/*============================================================================#
#                                 Functions                                   #
#============================================================================*/

//lexing/parsing
t_command  *parsing(char *s);
char	**parsing_split(const char *s, char c);
void  handle_expanding(char **s);
int  handle_quotes(t_command *command);
int	parse_out_in_files(t_command *command);
size_t skip_quotes(const char *s, size_t i);
void assign_redirect(t_command *command, int table_pos, int	arg_pos);

//parse_commands
int  parse_commands(t_command *command);
int parse_exit(t_simple_command *s);
int	parse_cd(t_simple_command *s);
int	parse_pwd_env(t_simple_command *s);
int parse_export_unset(t_simple_command *s);


//exiting/errors
void memory_free(char **s, t_command *command, int error);
void  ft_free(char	**ptr);
int print_error(int error_code);
#endif
