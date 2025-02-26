/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpedrosa <rpedrosa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 15:25:06 by rpedrosa          #+#    #+#             */
/*   Updated: 2025/02/26 17:02:04 by rpedrosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

static int check_path(char *s)
{
	int	i;

	i = 0;
	while(s[i])
	{
		//TODO
	}
	return (0);
}

int	parse_cd(t_simple_command *s)
{
	if (s->number_args > 2)
		return (print_error(TOO_MANY_ARGS));
	if (s->args[1])	
	{
		if (check_path(s->args[1]) != 0)
			return (1);
	}
	return (0);
}

//pwd e env nao can't take arguments 
int	parse_pwd_env(t_simple_command *s)
{
	if (s->number_args > 2)
		return (print_error(TOO_MANY_ARGS));
	return (0);
}

static int check_export_arg(char *s)
{
	int	i;

	i = 1;
	if (ft_isalpha(s[0]) != 1 && s[0] != '_')
		return (print_error(SYNTAX_ERROR));
	while (s[i] != '=' && s[i])
	{
		if (ft_isalpha(s[i]) != 1 && ft_isdigit(s[i]) != 1 && s[i] != '_')
			return (print_error(SYNTAX_ERROR));
		i++;
	}
	if (!s[i])
		return (print_error(SYNTAX_ERROR));
	if (s[i + 1] == '=')
		return (print_error(SYNTAX_ERROR));
	return (0);
}

//export e unset follow the same name rules:
//first char is always a letter;
//following name can have letter, '_' or digits;
//can have more then 1 '='
int parse_export_unset(t_simple_command *s)
{
	int	i;

	i = 1;
	if (s->number_args < 2)
		return (print_error(NO_ARGS));
	while (s->args[i++])
	{
		if (check_export_arg(s->args[i - 1]) != 0)
			return (1);
	}
	return (0);
}
