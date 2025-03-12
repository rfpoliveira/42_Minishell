/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpedrosa <rpedrosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 16:37:15 by rpedrosa          #+#    #+#             */
/*   Updated: 2025/03/12 17:00:52 by rpedrosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"
#include "../../incs/parsing.h"

static int check_redirect_error(t_simple_command *simple, int arg, int i)
{
	if (simple->args[arg][i] == '<')
	{
		if (simple->args[arg][i + 1] == '<' && \
			(simple->args[arg][i + 2] == '>' || \
			(simple->args[arg][i + 2] == '\0' \
			&& simple->args[arg + 1] && simple->args[arg + 1][0] == '>')))
			return (print_error(SYNTAX_ERROR), 1);
		else if ((simple->args[arg][i + 1] == '\0' && simple->args[arg + 1] && \
				(simple->args[arg + 1][0] == '>') || \
				simple->args[arg + 1][0] == '<') || \
				simple->args[arg][i + 1] == '>')
			return (print_error(SYNTAX_ERROR), 1);
	}
	else if (simple->args[arg][i] == '>')
	{
		if (simple->args[arg][i + 1] == '>' && (simple->args[arg][i + 2] == '<'\
			|| (simple->args[arg][i + 2] == '\0' && simple->args[arg + 1] \
			&& simple->args[arg + 1][0] == '<')))
			return (print_error(SYNTAX_ERROR), 1);
		else if ((simple->args[arg][i + 1] == '\0' && simple->args[arg + 1]) \
			&& (simple->args[arg + 1][0] == '<' || \
			simple->args[arg + 1][0] == '>') || simple->args[arg][i + 1] == '<')
			return (print_error(SYNTAX_ERROR), 1);
	}
	return (0);
}

static int	assign_redirects(t_simple_command *simple, char *file, int arg, char **buff, int flag)
{
	free(file);
	if (flag == 1 || flag == 2)
	{
		if (simple->args[arg + 1] == NULL)
			return (print_error(SYNTAX_ERROR) , 1);	
		file = ft_strdup(simple->args[arg + 1]);
	}
	if (flag == 3)
		file = ft_strdup(buff[1] + 1);
	if (flag == 4)
		file = ft_strdup(buff[0]);
	delete_args(simple, arg, buff, flag);
	return (0);
}

int	split_redirects(t_simple_command *simple, int arg, int i, char *red)
{
	char	**buff;
	int		buff_arg;
	char *file;
	int	error;

	buff_arg = 0;
	error = 0;
	file = ft_strdup("");
	buff = parsing_split(simple->args[arg], red[0]);
	while (buff[buff_arg])
		buff_arg++;
	if (buff_arg == 1 && (buff[0][1] == '\0' || \
		((buff[0][1] == '<' || buff[0][1] == '>') && buff[0][2] == '\0')))
		error = assign_redirects(simple, file, arg, buff, 1); // '<' ou '<<'
	else if (buff_arg == 1)
		error = assign_redirects(simple, file, arg, buff, 4); // '<ola' ou '<<ola'
	else if (buff_arg == 2 && i != 0 && buff[1][1] == '\0')
		error = assign_redirects(simple, file, arg, buff, 2); // 'ola>>' ou 'ola>'
	else if (buff_arg == 2)
		error = assign_redirects(simple, file, arg, buff, 3); // 'ola>>test' ou 'ola>test'
	if (error == 0)
		selecting_file(simple, red, file);
	free(file);
	matrix_free(buff);
	return (error);
}

static int	iter_red(t_command *command, int i)
{
	int	j;
	int x;
	
	j = -1;
	x = -1;
	while (command->table[i]->args[++j])
	{
		while (command->table[i]->args[j][++x])
		{
			if (command->table[i]->args[j][x] == 34 || \
				command->table[i]->args[j][x] == 39)
				x += skip_quotes(command->table[i]->args[j], x);
			if (command->table[i]->args[j][x] == '<' || \
				command->table[i]->args[j][x] == '>')
			{
				if (check_redirect_error(command->table[i], j , x) != 0 || \
					redirect_hopper(command->table[i], j , x) != 0)
					return (1);
				j = 0;
				break ;
			}
		}
		x = -1;
	}
	return (0);
}

int	handle_redirect(t_command *command)
{
	int	i;

	i = -1;

	while (command->table[++i])
	{
		if (iter_red(command, i) != 0)
			return (1);
	}
	return (0);
}
