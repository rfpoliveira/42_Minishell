/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpedrosa <rpedrosa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 14:55:27 by rpedrosa          #+#    #+#             */
/*   Updated: 2025/03/20 15:50:30 by rpedrosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#define _XOPEN_SOURCE 700

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
#include <signal.h>

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
#define EXIT_ERROR -8
#define STDIN_ERROR -9

/*============================================================================#
#								 STRUCTS									  #
#============================================================================*/

typedef struct s_simple_command
{
	int	number_args;
	char **args;
	char	*paths;
	char *infile;
	char *outfile;
	char *double_in;
	char *double_out;
}	t_simple_command;

typedef struct s_command
{
	int					number_simple_commands;
	t_simple_command  **table;
}	t_command;

typedef	struct s_envlist
{
	struct s_envlist	*next;
	struct s_envlist	*prev;
	char	*var;
}	t_env;

typedef	struct s_data
{
	t_command	*command;
	t_env		*env;
	char		**paths;
}	t_data;
/*============================================================================#
#                                 Functions                                   #
#============================================================================*/

#include "exec.h"
void    handle_signals(void);
t_command  *parsing(char *s, int *exit_code);

//exiting/errors
void memory_free(int *exit_code, char **s, t_command *command, int error);
void  ft_free(char	**ptr);
void print_error(int error_code, int *exit_code);
#endif
