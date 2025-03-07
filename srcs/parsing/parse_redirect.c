/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renato-oliveira <renato-oliveira@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 16:37:15 by rpedrosa          #+#    #+#             */
/*   Updated: 2025/03/07 14:50:32 by renato-oliv      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"
#include "../../incs/parsing.h"

static int check_redirect_error(t_simple_command *simple, int arg, int i)
{
	if (simple->args[arg][i] == '<')
	{
		if (simple->args[arg][i + 1] == '<' && (simple->args[arg][i + 2] == '>' || \
			(simple->args[arg][i + 2] == '\0' && simple->args[arg + 1][0] == '>')))
			return (print_error(SYNTAX_ERROR), 1);
		else if (simple->args[arg][i + 1] == '\0' && simple->args[arg + 1][0] == '>')
			return (print_error(SYNTAX_ERROR), 1);
		else if (simple->args[arg][i + 1] == '>')
			return (print_error(SYNTAX_ERROR), 1);
	}
	else if (simple->args[arg][i] == '>')
	{
		if (simple->args[arg][i + 1] == '>' && (simple->args[arg][i + 2] == '<' || \
			(simple->args[arg][i + 2] == '\0' && simple->args[arg + 1][0] == '<')))
			return (print_error(SYNTAX_ERROR), 1);
		else if (simple->args[arg][i + 1] == '\0' && simple->args[arg + 1][0] == '<')
			return (print_error(SYNTAX_ERROR), 1);
		else if (simple->args[arg][i + 1] == '<')
			return (print_error(SYNTAX_ERROR), 1);
	}
	return (0);
}

static void	assign_redirects(t_simple_command *simple, char **red, int arg, char **buff, int flag)
{
	if (flag == 1 && flag == 3)
		*red = simple->args[arg + 1];
	if (flag == 2)
		*red = ft_strdup(buff[0]);
	if (flag == 4)
		*red = ft_strdup(buff[1]);
	delete_args(simple, arg, buff, flag);
}

static void	split_redirects(t_simple_command *simple, int arg, int i, char *red)
{
	char	**buff;
	int		buff_arg;

	buff_arg = 0;
	buff = parsing_split(simple->args[arg], red[0]);
	string_to_pointer(simple, red);
	while (buff[buff_arg])
		buff_arg++;
	if (buff[0] == ft_strdup(""))
		assign_redirects(simple, &red, arg, buff, 1);
	else if (buff_arg == 1 && i == 0)
		assign_redirects(simple, &red, arg, buff, 2);
	else if (buff_arg == 1)
	{
		assign_redirects(simple, &red, arg, buff, 3);
		simple->args[arg][i] = '\0';
	}
	else
		assign_redirects(simple, &red, arg, buff, 4);
	matrix_free(buff);

}

static void redirect_hopper(t_simple_command *simple, int arg, int i)
{
	if (simple->args[arg][i] == '<')
	{
		if (simple->args[arg][i + 1] == '<')
			split_redirects(simple, arg, i, "<<");
		else if (simple->args[arg][i + 1] != '<')
			split_redirects(simple, arg, i, "<");
	}
	else if (simple->args[arg][i] == '>')
	{
		if (simple->args[arg][i + 1] == '>')
			split_redirects(simple, arg, i, ">>");
		else if (simple->args[arg][i + 1] != '>')
			split_redirects(simple, arg, i, ">");
	}
}

int	handle_redirect(t_command *command)
{
	int	i;
	int	j;
	int x;
	int	error;

	i = -1;
	j = 0;
	x = 0;
	error = 0;
	while (command->table[++i])
	{
		while (command->table[i]->args[j])
		{
			while (command->table[i]->args[j][x] != '\0')
			{
				if (command->table[i]->args[j][x] == '<' || command->table[i]->args[j][x] == '>')
				{
					error = check_redirect_error(command->table[i], j , x);
					redirect_hopper(command->table[i], j , x);
				}
				x++;
			}
			j++;
		}
	}
	return (error);
}