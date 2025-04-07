/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpedrosa <rpedrosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 15:11:31 by rpedrosa          #+#    #+#             */
/*   Updated: 2025/04/01 15:13:09 by rpedrosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	check_redirect_error_util(t_simple_command *simple, int *exit_code)
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