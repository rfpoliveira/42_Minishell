/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpedrosa <rpedrosa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 14:56:47 by rpedrosa          #+#    #+#             */
/*   Updated: 2025/03/20 16:44:30 by rpedrosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"
#include "../../incs/parsing.h"

//puts args back in order after the rederects been taken out
int	reorganize_args(t_simple_command *simple, int del, int del2)
{
	int	i;

	i = del + 1;
	if (del2 != 0)
	{
		i = del2 + 1;
		ft_free(&simple->args[del2]);
	}
	ft_free(&simple->args[del]);
	while (simple->args[i])
	{
		simple->args[del] = ft_strdup(simple->args[i]);
		if (simple->args[del] == NULL)
			return (1);
		ft_free(&simple->args[i]);
		i++;
		del++;
	}
	return (0);
}
//deletes arguments that we dont need anymore 
//probably the ones saved in the strcut for redirections
int	delete_args(t_simple_command *simple, int arg, char **buff, int flag)
{
	int	error;

	error = 0;
	if (flag == 1)
		error = reorganize_args(simple, arg, arg + 1);
	else if (flag == 2)
	{
		error = reorganize_args(simple, arg + 1, 0);
		delete_sigs(simple->args[arg], '>', '<', NULL);
	}
	else if (flag == 3)
	{
		ft_free(&simple->args[arg]);
		simple->args[arg] = ft_strdup(buff[0]);
	}
	else if (flag == 4)
		error = reorganize_args(simple, arg, 0);
	return (error);
}
//sleectes if the redirectipn will be a outfile, infile etc
int	selecting_file(t_simple_command *simple, char *red, char *file, int *exit_code)
{
	if (red[0] == '>' && red[1] == '\0')
	{
		simple->outfile = ft_strdup(file);
		if (simple->outfile == NULL)
			return (print_error(MALLOC_ERROR, exit_code), 1);
	}
	else if (red[0] == '>' && red[1] == '>')
	{
		simple->double_out = ft_strdup(file);
		if (simple->double_out == NULL)
			return (print_error(MALLOC_ERROR, exit_code), 1);
	}
	else if (red[0] == '<' && red[1] == '\0')
	{
		simple->infile = ft_strdup(file);
		if (simple->infile == NULL)
			return (print_error(MALLOC_ERROR, exit_code), 1);
	}
	else if (red[0] == '<' && red[1] == '<')
	{
		simple->double_in = ft_strdup(file);
		if (simple->double_in == NULL)
			return (print_error(MALLOC_ERROR, exit_code), 1);
	}
	return (0);
}

//detects what type of redirection we dealing with
int	redirect_hopper(t_simple_command *simple, int arg, int i, int *exit_code)
{
	int	error;

	error = 0;
	if (simple->args[arg][i] == '<')
	{
		if (simple->args[arg][i + 2] && \
			(simple->args[arg][i + 1] == '<' || \
			simple->args[arg][i + 1] == '>'))
			return (print_error(SYNTAX_ERROR, exit_code), 1);
		else if (simple->args[arg][i + 1] == '<')
			error = split_redirects(exit_code, simple, arg, i, "<<");
		else if (simple->args[arg][i + 1] != '<')
			error = split_redirects(exit_code, simple, arg, i, "<");
	}
	else if (simple->args[arg][i] == '>')
	{
		if (simple->args[arg][i + 2] && (simple->args[arg][i + 1] == '<' \
			|| simple->args[arg][i + 1] == '>'))
			return (print_error(SYNTAX_ERROR, exit_code), 1);
		else if (simple->args[arg][i + 1] == '>')
			error = split_redirects(exit_code, simple, arg, i, ">>");
		else if (simple->args[arg][i + 1] != '>')
			error = split_redirects(exit_code, simple, arg, i, ">");
	}
	return (error);
}
