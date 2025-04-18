/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpedrosa <rpedrosa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 15:25:06 by rpedrosa          #+#    #+#             */
/*   Updated: 2025/03/20 15:37:03 by rpedrosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"
#include "../../incs/parsing.h"

//check if the path is valid or not
static int	check_path(char *s, int *exit_code)
{
	DIR	*dir;

	dir = opendir(s);
	if (dir)
	{
		closedir(dir);
		return (0);
	}
	else if (ENOENT == errno)
		return (print_error(INV_PATH, exit_code), 1);
	else
		return (print_error(OPEN_ERROR, exit_code), 1);
}

//cd can only have 1 argument and I chekc if the path is valid or exists
int	parse_cd(t_simple_command *s, int *exit_code)
{
	int	i;

	i = 1;
	if ((s->number_args > 2 && s->args[0][0] != '|') || \
	(s->number_args > 3 && s->args[0][0] == '|'))
		return (print_error(TOO_MANY_ARGS, exit_code), 1);
	if (s->args[0][0] == '|')
		i++;
	if (s->args[i])
	{
		if (check_path(s->args[i], exit_code) != 0)
			return (1);
	}
	return (0);
}

//env nao can't take arguments 
int	parse_env(t_simple_command *s, int *exit_code)
{
	int	args;

	args = 1;
	if (s->args[0][0] == '|')
		args++;
	if (s->number_args > args)
		return (print_error(TOO_MANY_ARGS, exit_code), 1);
	return (0);
}

static int	check_export_arg(char *s, int *exit_code)
{
	int	i;

	i = 1;
	if (ft_isalpha(s[0]) != 1 && s[0] != '_')
		return (print_error(SYNTAX_ERROR, exit_code), 1);
	while (s[i] != '=' && s[i])
	{
		if (ft_isalpha(s[i]) != 1 && ft_isdigit(s[i]) != 1 && s[i] != '_')
			return (print_error(SYNTAX_ERROR, exit_code), 1);
		i++;
	}
	if (!s[i])
		return (print_error(SYNTAX_ERROR, exit_code), 1);
	if (s[i + 1] == '=')
		return (print_error(SYNTAX_ERROR, exit_code), 1);
	return (0);
}

//export e unset follow the same name rules:
//first char is always a letter;
//following name can have letter, '_' or digits;
//can have more then 1 '='
int	parse_export_unset(t_simple_command *s, int *exit_code)
{
	int	i;

	i = 1;
	if (s->number_args < 2)
		return (print_error(NO_ARGS, exit_code), 1);
	while (s->args[i++])
	{
		if (check_export_arg(s->args[i - 1], exit_code) != 0)
			return (1);
	}
	return (0);
}
