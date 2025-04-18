/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpedrosa <rpedrosa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 14:30:00 by rpedrosa          #+#    #+#             */
/*   Updated: 2025/04/17 11:12:29 by rpedrosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"
#include "../../incs/parsing.h"
/* @brief: substituits the contents of s ($$) with the exit code of the last command 
	@return: 0 in case of success
			 1 or any other number in case of error (Malloc)*/
int	expande_exit_code(char **s, int *exit_code)
{
	free(*s);
	*s = ft_itoa(*exit_code);
	if (*s == NULL)
		return (print_error(MALLOC_ERROR, exit_code), 1);
	return (0);
}
/* @brief: allocs and gets whats before whats being expanded
	@arguments: s is the string where the expand symbol ($) is found.
				x - 1 is the index where "$" is found in s.
	the first condicion checks if there is anything to save and saves it,
	if not it allocs an empty string to have something to free in either, facilitating that.
	@return: a string allocated with whats before the "$" sign
			 NULL in case of malloc error */
char	*get_prev(char *s, int x)
{
	char *prev;
	
	if (x != 1)
	{
		prev = ft_substr(s, 0, x - 1);
		if (!prev)
			return (NULL);
		prev[x - 1] = '\0';	
	}
	else
	{
		prev = ft_strdup("");
			if (!prev)
				return (NULL);
	}
	return (prev);
}
/* @brief: gets the string that should be expanded and does so
	@arguments: s is a pointer to the "$" in the string.
				x is position in the string next to the "$".
				env is the pointer where we save the expanded environment variable.
	@notes: takes len does if finds 34(double quote) cuz is supposed to expand anyway.
			gets only the enviroment var name to tmp ready to use in getenv.
	@return: 0 in case of success. 
			 MALLOC_ERROR or any number in case of error */
int my_get_env(char *s, char **env, int x)
{
	char *tmp;
	int	len;

	len = ft_strlen(s);
	if (s[len - 1] == 34)
		len--;
	len -= x;
	tmp = ft_substr(s, x, len);
	if (!tmp)
		return (MALLOC_ERROR);
	*env = getenv(tmp);
	return (free(tmp), 0);
}

int	get_str(char **s, char *prev, char *env, int len)
{
	if ((*s)[len - 2] == 34)
		len--;
	free(*s);
	*s = ft_calloc(len, sizeof(char));
	if (!(*s))
		return (MALLOC_ERROR);
	ft_strlcat(*s, prev, len);
	if (env)
		ft_strlcat(*s, env, len);
	return (0);
}
