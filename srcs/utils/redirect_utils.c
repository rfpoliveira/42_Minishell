/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpedrosa <rpedrosa@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 12:32:45 by renato-oliv       #+#    #+#             */
/*   Updated: 2025/03/07 12:32:45 by renato-oliv      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"
#include "../../incs/parsing.h"

//puts args back in order after the rederects been taken out
void	reorganize_args(t_simple_command *simple, int del, int del2)
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
		ft_free(&simple->args[i]);
		i++;
		del++;
	}
}
//deletes arguments that we dont need anymore 
//probably the ones saved in the strcut for redirections
void	delete_args(t_simple_command *simple, int arg, char **buff, int flag)
{
	if (flag == 1)
		reorganize_args(simple, arg, arg + 1);
	if (flag == 2)
	{
		reorganize_args(simple, arg + 1, 0);
		delete_sigs(simple->args[arg], '>', '<');
	}
	if (flag == 3)
	{
		ft_free(&simple->args[arg]);
		simple->args[arg] = ft_strdup(buff[0]);
	}
	if (flag == 4)
		reorganize_args(simple, arg, 0);
}
//sleectes if the redirectipn will be a outfile, infile etc
void	selecting_file(t_simple_command *simple, char *red, char *file)
{
	if (red[0] == '>' && red[1] == '\0')
		simple->outfile = ft_strdup(file);
	else if (red[0] == '>' && red[1] == '>')
		simple->double_out = ft_strdup(file);
	else if (red[0] == '<' && red[1] == '\0')
		simple->infile = ft_strdup(file);
	else if (red[0] == '<' && red[1] == '<')
		simple->double_in = ft_strdup(file);
}
//detects what type of redirection we dealing with
int	redirect_hopper(t_simple_command *simple, int arg, int i)
{
	int	error;

	error = 0;
	if (simple->args[arg][i] == '<')
	{
		if (simple->args[arg][i + 2] && \
			(simple->args[arg][i + 1] == '<' || \
			simple->args[arg][i + 1] == '>'))
			return (print_error(SYNTAX_ERROR), 1);
		else if (simple->args[arg][i + 1] == '<')
			error = split_redirects(simple, arg, i, "<<");
		else if (simple->args[arg][i + 1] != '<')
			error = split_redirects(simple, arg, i, "<");
	}
	else if (simple->args[arg][i] == '>')
	{
		if (simple->args[arg][i + 2] && (simple->args[arg][i + 1] == '<' \
			|| simple->args[arg][i + 1] == '>'))
			return (print_error(SYNTAX_ERROR), 1);
		else if (simple->args[arg][i + 1] == '>')
			error = split_redirects(simple, arg, i, ">>");
		else if (simple->args[arg][i + 1] != '>')
			error = split_redirects(simple, arg, i, ">");
	}
	return (error);
}
