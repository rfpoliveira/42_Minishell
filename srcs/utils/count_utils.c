/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpedrosa <rpedrosa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 15:49:43 by rpedrosa          #+#    #+#             */
/*   Updated: 2025/06/27 15:23:23 by rpedrosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"
#include "../../incs/parsing.h"

void	count_everything(t_data *command, int i)
{
	t_simple_command	*current;

	current = command->table[i];
	current->number_args = count_args(current);
	current->numb_ins = count_infiles(current->args);
	current->numb_outs = count_outfiles(current->args);
	current->numb_double_ins = count_double_ins(current->args);
	current->numb_double_outs = count_double_outs(current->args);
}

/**
 @brief counts the number of infiles in the current argument
 @return int that represent the count
*/
int	count_infiles(char **current)
{
	int	j;
	int	i;
	int	count;

	j = -1;
	count = 0;
	while (current[++j])
	{
		i = 0;
		while (current[j][i])
		{
			if (current[j][i] == 39 || current[j][i] == 34)
				i += skip_quotes(current[j], i);
			if (current[j][i] == '<' && current[j][i + 1] != '<')
			{
				if (i == 0)
					count++;
				else if (i > 0 && current[j][i - 1] != '<')
					count++;
			}
			if (current[j][i])
				i++;
		}
	}
	return (count);
}

/** 
 @brief counts the number of outfiles in the current argument
 @return int that represent the count
*/
int	count_outfiles(char **current)
{
	int	j;
	int	i;
	int	count;

	j = -1;
	count = 0;
	while (current[++j])
	{
		i = 0;
		while (current[j][i])
		{
			if (current[j][i] == 39 || current[j][i] == 34)
				i += skip_quotes(current[j], i);
			if (current[j][i] == '>' && current[j][i + 1] != '>')
			{
				if (i == 0)
					count++;
				else if (i > 0 && current[j][i - 1] != '>')
					count++;
			}
			if (current[j][i])
				i++;
		}
	}
	return (count);
}

/** 
 @brief counts the number of "<<" in the current argument
 @return int that represent the count
*/
int	count_double_ins(char **current)
{
	int	j;
	int	i;
	int	count;

	j = -1;
	i = 0;
	count = 0;
	while (current[++j])
	{
		while (current[j][i])
		{
			if (current[j][i] == 39 || current[j][i] == 34)
				i += skip_quotes(current[j], i);
			if (current[j][i] == '<' && current[j][i] \
			&& current[j][i + 1] == '<')
			{
				count++;
				i++;
			}
			if (current[j][i])
				i++;
		}
		i = 0;
	}
	return (count);
}

/**
 @brief counts the number of ">>" in the current argument
 @return int that represent the count
*/
int	count_double_outs(char **current)
{
	int	j;
	int	i;
	int	count;

	j = -1;
	i = 0;
	count = 0;
	while (current[++j])
	{
		while (current[j][i])
		{
			if (current[j][i] == 39 || current[j][i] == 34)
				i += skip_quotes(current[j], i);
			if (current[j][i] == '>' && current[j][i + 1] == '>')
			{
				count++;
				i++;
			}
			if (current[j][i])
				i++;
		}
		i = 0;
	}
	return (count);
}
