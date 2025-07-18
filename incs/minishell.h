/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpedrosa <rpedrosa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 14:55:27 by rpedrosa          #+#    #+#             */
/*   Updated: 2025/07/08 18:51:18 by rpedrosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/*============================================================================#
#								libraries									  #
#============================================================================*/

# include "../libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <dirent.h>
# include <string.h>
# include <sys/ioctl.h>
# include <termios.h>
# include <curses.h>
# include <term.h>
# include <errno.h>
# include <signal.h>
# include <fcntl.h>
# include <unistd.h>

# define _XOPEN_SOURCE 700

extern int	g_sigint_flag;
/*============================================================================#
#								  ERRORS									  #
#============================================================================*/

# define MALLOC_ERROR 1
# define QUOTE_ERROR -1
# define COM_NOT_FOUND -2
# define TOO_MANY_ARGS -3
# define INV_PATH -4
# define NO_ARGS -5
# define SYNTAX_ERROR -6
# define OPEN_ERROR -7
# define EXIT_ERROR -8
# define STDIN_ERROR -9
# define AMBI_REDI -10

/*============================================================================#
#								 STRUCTS									  #
#============================================================================*/

typedef struct s_envlist
{
	struct s_envlist	*next;
	struct s_envlist	*prev;
	char				*key;
	char				*value;
}	t_env;

typedef struct s_iters
{
	int	in_iter;
	int	out_iter;
	int	double_out_iter;
}	t_iters;

typedef struct s_simple_command
{
	int		number_args;
	char	**args;
	char	*paths;
	int		fd[2];
	char	**infile;
	char	**outfile;
	char	**double_in;
	char	**double_out;
	int		out_iter;
	int		in_iter;
	char	*red_order;
	int		numb_ins;
	int		numb_outs;
	int		numb_double_outs;
	int		numb_double_ins;
	t_iters	*iters;
}			t_simple_command;

typedef struct s_data
{
	int					number_simple_commands;
	t_simple_command	**table;
	int					exit_code;
	t_env				*env;
	char				**envp;
	char				**hd;
	char				**paths;
	char				*prompt;
}						t_data;

/*============================================================================#
#                                 Functions                                   #
#============================================================================*/

void	handle_signals(void);
void	alloc_struct(t_data **command);
char	*get_prompt(t_data *data);
void	handle_history(char **user_line);
int		parsing(char **user_line, t_data *command);

//exiting/errors/memory
void	memory_free(char **s, t_data *command, int error);
void	command_free(t_data **command);
void	table_free(t_simple_command **table);
void	ft_free(char **ptr);
void	inoutfiles_free(t_simple_command *table);
void	print_error(int error_code, int *exit_code);
void	exit_bash(char **prompt, t_data *command, int exit_code);

#endif
