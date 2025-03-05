/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpedrosa <rpedrosa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 15:09:43 by rpedrosa          #+#    #+#             */
/*   Updated: 2025/02/26 16:59:53 by rpedrosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/parsing.h"
#include "../../incs/minishell.h"

static int check_built_in(t_simple_command *s)
{
	struct stat res_buff;
	char **splited_path;
	char *joined_path;
	char  *command;
	int	i;

	i = 0;
	joined_path = NULL;
	command = ft_strjoin("/", s->args[0]);
	splited_path = ft_split(getenv("PATH"), ':');
	while (splited_path[i])
	{
		joined_path = ft_strjoin(splited_path[i], command);
		if (stat(joined_path, &res_buff) == 0)
			return (matrix_free(splited_path), free(joined_path), free(command), 0);
		free(joined_path);
		joined_path = NULL;
		i++;
	}
	return(matrix_free(splited_path), free(command), print_error(COM_NOT_FOUND));
}

static int detect_command(t_simple_command *s)
{
	if (ft_strncmp(s->args[0], "echo", 4) == 0)
		return (0);
	else if (ft_strncmp(s->args[0], "cd", 2) == 0)
		return (parse_cd(s));
	else if (ft_strncmp(s->args[0], "pwd", 3) == 0)
		return (parse_pwd_env(s));
	else if (ft_strncmp(s->args[0], "export", 6) == 0)
		return (parse_export_unset(s));
	else if (ft_strncmp(s->args[0], "unset", 5) == 0)
		return (parse_export_unset(s));
	else if (ft_strncmp(s->args[0], "env", 3) == 0)
		return (parse_pwd_env(s));
	else if (ft_strncmp(s->args[0], "exit", 4) == 0)
		return (parse_exit(s));
	else
		return (check_built_in(s));
	return (print_error(COM_NOT_FOUND));
}

int  parse_commands(t_command *command)
{
	int	i;

	i = -1;
	while (command->table[++i])
	{
		if (detect_command(command->table[i]) != 0)
			return (1);
	}
	return (0);
}
