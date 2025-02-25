
#ifndef MINISHELL_H
# define MINISHELL_H

/*============================================================================# #                                 Libraries                                   #
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

/*============================================================================#
#								libraries									  #
#============================================================================*/

#define MALLOC_ERROR 1
#define QUOTE_ERROR -1

/*============================================================================#
#								libraries									  #
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
void  handle_quotes(t_command *command);

//exiting
void exiting_program(char **s, t_command *command, int error);
void  ft_free(void	*ptr);
void print_error(int error_code);
#endif
