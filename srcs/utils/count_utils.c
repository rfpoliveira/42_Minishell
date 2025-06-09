/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpedrosa <rpedrosa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 15:49:43 by rpedrosa          #+#    #+#             */
/*   Updated: 2025/06/09 17:17:15 by rpedrosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

/**
 @brief counts the number of infiles in the current argument
 @return int that represent the count
*/
int	count_infiles(char **current)
{
	int	j;
	int	i;
	int	count;

	j = 0;
	i = 0;
	count = 0;
	while (current[j])
	{
		while (current[j][i])
		{
			if (current[j][i] == '<' && current[j][i + 1] != '<')
			{
				if (i == 0)
					count++;
				else if (i > 0 && current[j][i - 1] != '<')
					count++;
			}
			i++;
		}
		i = 0;
		j++;
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

	j = 0;
	i = 0;
	count = 0;
	while (current[j])
	{
		while (current[j][i])
		{
			if (current[j][i] == '>' && current[j][i + 1] != '>')
			{
				if (i == 0)
					count++;
				else if (i > 0 && current[j][i - 1] != '>')
					count++;
			}
			i++;
		}
		i = 0;
		j++;
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
	i = -1;
	count = 0;
	while (current[++j])
	{
		while (current[j][++i])
		{
			if (current[j][i] == '<' && current[j][++i] == '<')
				count++;
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
	i = -1;
	count = 0;
	while (current[++j])
	{
		while (current[j][++i])
			if (current[j][i] == '>' && current[j][++i] == '>')
				count++;
		i = -1;
	}
	return (count);
}
