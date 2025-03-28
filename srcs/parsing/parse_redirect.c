/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpedrosa <rpedrosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 16:37:15 by rpedrosa          #+#    #+#             */
/*   Updated: 2025/03/27 15:13:37 by rpedrosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"
#include "../../incs/parsing.h"

//check if we dont have cases like: echo ola >> >text
static int	check_redirect_error(t_simple_command *simple, int *exit_code)
{
	if (simple->infile)
	{
		if (simple->infile[0] == '<' || simple->infile[0] == '>')
			return (print_error(SYNTAX_ERROR, exit_code), 1);
	}
	if (simple->outfile)
	{
		if (simple->outfile[0] == '<' || simple->outfile[0] == '>')
			return (print_error(SYNTAX_ERROR, exit_code), 1);
	}
	if (simple->double_in)
	{
		if (simple->double_in[0] == '<' || simple->double_in[0] == '>')
			return (print_error(SYNTAX_ERROR, exit_code), 1);
	}
	if (simple->double_out)
	{
		if (simple->double_out[0] == '<' || simple->double_out[0] == '>')
			return (print_error(SYNTAX_ERROR, exit_code), 1);
	}
	return (0);
}
//puts the correct rederect string in the correct pointer
static int	assign_redirects(t_simple_command *simple, int *exit_code, char *file, int arg, char **buff, int flag)
{
	free(file);
	if (flag == 1 || flag == 2)
	{
		if (simple->args[arg + 1] == NULL)
			return (print_error(SYNTAX_ERROR, exit_code), 1);
		file = ft_strdup(simple->args[arg + 1]);
	}
	if (flag == 3)
		file = ft_strdup(buff[1] + 1);
	if (flag == 4)
		file = ft_strdup(buff[0]);
	if (file == NULL)
		return (print_error(MALLOC_ERROR, exit_code), 1);
	if (delete_args(simple, arg, buff, flag) != 0)
		return (print_error(MALLOC_ERROR, exit_code), 1);
	return (0);
}
//if (1): '>'
//if (2): '<ola' ou '<<ola'
//if (3): 'ola>>' ou 'ola>'
//if (4): 'ola>>test' ou 'ola>test'
//with the cases above it takes it assigns a flag to the correct 
//method of separating the rederecting string name and the rest of the args
int	split_redirects(int *exit_code, t_simple_command *simple, int arg, int i, char *red)
{
	char	**buff;
	int		buff_arg;
	char	*file;
	int		error;

	buff_arg = 0;
	error = 0;
	file = ft_strdup("");
	buff = parsing_split(simple->args[arg], red[0]);
	if (file == NULL || buff == NULL)
	{
		print_error(MALLOC_ERROR, exit_code);
		error = MALLOC_ERROR;
	}
	while (buff[buff_arg])
		buff_arg++;
	if (buff_arg == 1 && (buff[0][1] == '\0' || \
		((buff[0][1] == '<' || buff[0][1] == '>') && buff[0][2] == '\0')))
		error = assign_redirects(simple, exit_code, file, arg, buff, 1);
	else if (buff_arg == 1)
		error = assign_redirects(simple, exit_code, file, arg, buff, 4);
	else if (buff_arg == 2 && i != 0 && buff[1][1] == '\0')
		error = assign_redirects(simple, exit_code, file, arg, buff, 2);
	else if (buff_arg == 2)
		error = assign_redirects(simple, exit_code, file, arg, buff, 3);
	if (error == 0)
		error = selecting_file(simple, red, file, exit_code);
	ft_free(&file);
	matrix_free(buff);
	return (error);
}
//iterates threw all the "simple commands" ignoring quotes checking if 
//there is a redirection symbol 
static int	iter_red(t_command *command, int i)
{
	int	j;
	int	x;

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
				if (redirect_hopper(command->table[i], j, x, &command->exit_code) != 0 || \
					check_redirect_error(command->table[i], &command->exit_code) != 0)
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
