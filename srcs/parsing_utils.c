/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpedrosa <rpedrosa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 15:25:40 by rpedrosa          #+#    #+#             */
/*   Updated: 2025/02/25 15:31:59 by rpedrosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

int	parse_out_in_files(t_command *command)
{
	int	i;
	int j;
	
	i = 0;
	j = 0;
	while (command->table[i])
	{
		while (command->table[i]->infile[j])
		{
			if (command->table[i]->infile[j + 1] == 34 || command->table[i]->infile[j + 1] == 39)
				j = skip_quotes(command->table[i]->infile, j);
			
		}
	}
}

int	after_quote_strlen(char	*s)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (s)
	{
		while (s[i])
		{
			if (s[i] != 34 && s[i] != 39)
				count++;
			i++;
		}
	}
	return (count);
}

void  delete_quotes(char *s)
{
	int	i;
	char*  temp;
	int	len;

	i = 0;
	len = after_quote_strlen(s);
	temp = malloc(len + 1);
	temp[len] = '\0';
	len = 0;
	while (s[i])
	{
		if (s[i] != 34 && s[i] != 39)
		{
			temp[len] = s[i];
			len++;
		}
		i++;
	}
	ft_strlcpy(s, temp, len + 1);
	free(temp);
}

void  handle_quotes(t_command *command)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while(command->table[i])
	{
		while(command->table[i]->args[j])
		{
			delete_quotes(command->table[i]->args[j]);
			j++;
		}
		j = 0;
		i++;
	}
}
