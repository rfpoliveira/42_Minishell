
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
	char *double_in;
	char *double_out;
}	t_simple_command;

typedef struct s_command
{
	int number_simple_commands;
	t_simple_command  **table;
}	t_command;

/*============================================================================#
#                                 Functions                                   #
#============================================================================*/

t_command  *parsing(char *s);

//exiting/errors
void memory_free(char **s, t_command *command, int error);
void  ft_free(char	**ptr);
void print_error(int error_code);
#endif
