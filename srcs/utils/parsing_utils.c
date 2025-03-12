/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpedrosa <rpedrosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 15:25:40 by rpedrosa          #+#    #+#             */
/*   Updated: 2025/03/12 10:34:08 by rpedrosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/parsing.h"
#include "../../incs/minishell.h"

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
void  delete_sigs(char *s, char A, char B)
{
	int	i;
	char*  temp;
	int	len;

	i = 0;
	if (s == NULL)
		return ;
	len = after_sig_strlen(s, A, B);
	temp = malloc(len + 1);
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
}

int	ft_isspace(char c)
{
	if (c == 32 || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

int	check_first_pipe(char *s)
{
	int	i;

	i = 0;
	while (s[i] && ft_isspace(s[i]))
		i++;
	if (s[i] == '|')
		return  (0);
	return (1);
}

int  handle_quotes(t_command *command)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while(command->table[i])
	{
		while(command->table[i]->args[j])
		{
			delete_sigs(command->table[i]->args[j], 34, 39);
			j++;
		}
		delete_sigs(command->table[i]->infile, 34, 39);
		delete_sigs(command->table[i]->outfile, 34, 39);
		delete_sigs(command->table[i]->double_in, 34, 39);
		delete_sigs(command->table[i]->double_out, 34, 39);
		j = 0;
		i++;
	}
	return (0);
}
