/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpedrosa <rpedrosa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 15:25:40 by rpedrosa          #+#    #+#             */
/*   Updated: 2025/03/20 16:29:54 by rpedrosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"
#include "../../incs/parsing.h"

//strlen but ignore A and B
static int	after_sig_strlen(char	*s, char A, char B)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (s)
	{
		while (s[i])
		{
			if (s[i] != A && s[i] != B)
				count++;
			i++;
		}
	}
	return (count);
}
//deletes A and B from the string (used to take out quotes
//and redirect symbls in some edge cases)
int	delete_sigs(char *s, char A, char B, int *exit_code)
{
	int		i;
	char	*temp;
	int		len;

	i = 0;
	if (s == NULL)
		return (0);
	len = after_sig_strlen(s, A, B);
	temp = malloc(len + 1);
	if (temp == NULL)
		return (print_error(MALLOC_ERROR, exit_code), 1);
	temp[len] = '\0';
	len = 0;
	while (s[i])
	{
		if (s[i] != A && s[i] != B)
		{
			temp[len] = s[i];
			len++;
		}
		i++;
	}
	ft_strlcpy(s, temp, len + 1);
	free(temp);
	return (0);
}

int	ft_isspace(char c)
{
	if (c == 32 || (c >= 9 && c <= 13))
		return (1);
	return (0);
}
//check if the first thing in the command is a pipe
int	check_first_pipe(char *s)
{
	int	i;

	i = 0;
	while (s[i] && ft_isspace(s[i]))
		i++;
	if (s[i] == '|')
		return (0);
	return (1);
}
//deletes quotes from everything
int	handle_quotes(t_command *command, int *exit_code)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (command->table[i])
	{
		while (command->table[i]->args[j])
		{
			delete_sigs(command->table[i]->args[j], 34, 39, exit_code);
			j++;
		}
		delete_sigs(command->table[i]->infile, 34, 39, exit_code);
		delete_sigs(command->table[i]->outfile, 34, 39, exit_code);
		delete_sigs(command->table[i]->double_in, 34, 39, exit_code);
		delete_sigs(command->table[i]->double_out, 34, 39, exit_code);
		j = 0;
		i++;
	}
	return (0);
}
