/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpedrosa <rpedrosa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 14:30:00 by rpedrosa          #+#    #+#             */
/*   Updated: 2025/05/23 13:38:38 by rpedrosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"
#include "../../incs/parsing.h"

/**
 @brief allocs and gets whats before whats being expanded
 
 	the first condicion checks if there is anything to save and saves it,
	if not it allocs an empty string to have 
	something to free in either, facilitating that.
	
 @param s is the string where the expand symbol ($) is found.
 @param x is the index after the one where "$" is found in s.
 @return a string allocated with whats before the "$" sign,
		 NULL in case of malloc error 
*/
char	*get_prev(char *s, int x)
{
	char	*prev;

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

/**
 @brief puts env and post together.
 @param tmp is a buffer.
 @param env is the pointer where we save the expanded 
			environment variable;
 @param post is what comes after the expanded variable;
*/
static void	apend_post(char **tmp, char **env, char *post)
{
	int	len;

	len = 0;
	if (!*env)
		*env = ft_strdup(post);
	else
	{
		ft_free(tmp);
		len = ft_strlen(*env) + ft_strlen(post) + 1;
		*tmp = malloc(len);
		if (*tmp == NULL)
		{
			ft_free(env);
			return ;
		}
		ft_strlcpy(*tmp, *env, len);
		ft_strlcat(*tmp, post, len);
		ft_free(env);
		*env = ft_strdup(*tmp);
	}
}

/**
 @brief gets the string that should be expanded and does so
 @param s is a pointer to the "$" in the string.
 @param x is position in the string next to the "$".
 @param env is the pointer where we save the expanded 
			environment variable;
 @note takes len does if finds 34(double quote) 
		cuz is supposed to expand anyway;
		gets only the enviroment var name 
		to tmp ready to use in getenv;
 @return 0 in case of success,
		 MALLOC_ERROR or any number in case of error 
*/
static int	get_len(char *s, int *i, int x)
{
	if (ft_isdigit(s[*i]) || s[*i] == '?' || s[*i] == '$')
		return (++(*i) - x);
	while (s[*i] && (ft_isalnum(s[*i]) || s[*i] == '_'))
		(*i)++;
	return (*i - x);
}

int	my_get_env(char *s, char **env, int x, int *exit_code)
{
	char	*tmp;
	char	*post;
	int		len;
	int		i;

	i = x;
	len = get_len(s, &i, x);
	tmp = ft_substr(s, x, len);
	if (!tmp)
		return (MALLOC_ERROR);
	post = ft_substr(s, i, ft_strlen(s));
	if (!post)
		return (free(tmp), MALLOC_ERROR);
	if (s[x] == '?')
		expande_exit_code(env, exit_code);
	else if (s[x++] == '$')
		*env = ft_strdup("");
	else
		*env = ft_strdup(getenv(tmp));
	apend_post(&tmp, env, post);
	if (!*env)
		return (ft_free(&tmp), ft_free(&post), MALLOC_ERROR);
	return (ft_free(&tmp), ft_free(&post), 0);
}

/**
 @brief takes the original string (s) with something to expande
		and substituits it for a new string with and variable
		expanded (env)
 @param s is the original string (must be a double pointer
		  because we will alter the pointer itself);
 @param prev is whay comes before the '$';
 @param env is the expanded variable;
 @param len is the total lenght of the new string;
 @note if we find a $ bettewn quotes(34 in ascii) we still need to
	   expande 
*/
int	get_str(char **s, char *prev, char *env, int len)
{
	if ((*s)[ft_strlen(*s) - 1] == 34)
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
