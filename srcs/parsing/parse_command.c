/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpedrosa <rpedrosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 15:09:43 by rpedrosa          #+#    #+#             */
/*   Updated: 2025/03/27 15:05:38 by rpedrosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/parsing.h"
#include "../../incs/minishell.h"

//check if the command exist in back
static int	check_built_in(t_simple_command *s, int *exit_code)
{
	struct stat	res_buff;
	char		**splited_path;
	char		*joined_path;
	char		*command;
	int			i;

	i = 0;
	joined_path = NULL;
	if (s->args[0][0] != '|')
		command = ft_strjoin("/", s->args[0]);
	else
		command = ft_strjoin("/", s->args[1]);
	splited_path = ft_split(getenv("PATH"), ':');
	while (splited_path[i])
	{
		joined_path = ft_strjoin(splited_path[i], command);
		if (stat(joined_path, &res_buff) == 0)
			return (matrix_free(splited_path), \
			free(joined_path), free(command), 0);
		free(joined_path);
		joined_path = NULL;
		i++;
	}
	return (matrix_free(splited_path), free(command), \
			print_error(COM_NOT_FOUND, exit_code), 1);
}
//check if there is a pipe in the beginning of the command
static int	check_pipes(t_simple_command *s, int *i, int *exit_code)
{
	if (s->args[0][0] == '|')
	{
		if (!s->args[0][1])
			(*i)++;
	}
	if (!s->args[*i])
		return (print_error(SYNTAX_ERROR, exit_code), 1);
	return (0);
}
//check if the command is one of the ones we need to implement
//and takes it to the parsing of its own
static int	detect_command(t_simple_command *s, int *exit_code)
{
	int	i;

	i = 0;
	if (check_pipes(s, &i, exit_code) != 0)
		return (1);
	if (s->args[i][0] == '|')
		s->args[i]++;
	if (ft_strncmp(s->args[i], "echo", 4) == 0)
		return (0);
	else if (ft_strncmp(s->args[i], "cd", 2) == 0)
		return (parse_cd(s, exit_code));
	else if (ft_strncmp(s->args[i], "pwd", 3) == 0)
		return (0);
	else if (ft_strncmp(s->args[i], "export", 6) == 0)
		return (parse_export_unset(s, exit_code));
	else if (ft_strncmp(s->args[i], "unset", 5) == 0)
		return (parse_export_unset(s, exit_code));
	else if (ft_strncmp(s->args[i], "env", 3) == 0)
		return (parse_env(s, exit_code));
	else if (ft_strncmp(s->args[i], "exit", 4) == 0)
		return (parse_exit(s, exit_code));
	else if (check_built_in(s, exit_code) == 0)
		return (0);
	return (1);
}

int	parse_commands(t_command *command)
{
	int	i;

	i = -1;
	while (command->table[++i])
	{
		if (detect_command(command->table[i], &command->exit_code) != 0)
			return (1);
	}
	return (0);
}
