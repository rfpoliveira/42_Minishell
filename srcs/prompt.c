/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpedrosa <rpedrosa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 16:54:00 by rpedrosa          #+#    #+#             */
/*   Updated: 2025/04/16 13:42:07 by rpedrosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

/* @brief: parses the path to mimic bash
	check if there is a /home/ in the
	begining (there is not if you at home) substituits that out
	for a "~" like bash does 
	@return: 1 in case of a malloc error
			 0 if there are no erros */
static int parse_path(char *user, char **path)
{
	int		check_len;
	char	*temp;

	check_len = 0;
	check_len = 6 + ft_strlen(user);
	temp = ft_calloc(check_len, sizeof(char));
	if (temp == NULL)
		return (1);
	ft_strlcat(temp, "/home/", check_len);
	ft_strlcat(temp, user, check_len);
	if (ft_strncmp(*path, temp, check_len - 1) == 0)
	{
		free(temp);
		temp = ft_strdup(*path + check_len);
		if (temp == NULL)
			return (1);
		free(*path);
		check_len = ft_strlen(temp) + 2;
		*path = ft_calloc(check_len, sizeof(char));
		if (*path == NULL)
			return (ft_free(&temp), 1);
		(*path)[0] = '~';
		ft_strlcat(*path, temp, check_len);
	}
	return (ft_free(&temp), 0);
}
/* @brief: puts the arguments recieved in a unique prompt
	first it alter the path then fuses everything 
	mimicing the bash prompt
	@return: in case of malloc errors returns null
	else returns the correct prompt*/
static char    *join_everything(char *user, char *path, char *hostname)
{
    char    *prompt;
    int     sum_len;

    sum_len = 0;
	if (parse_path(user, &path) != 0)
		return (ft_free(&hostname), ft_free(&path), NULL);
    sum_len = ft_strlen(user) + ft_strlen(path) + ft_strlen(hostname) + 5;
    prompt = ft_calloc(sum_len, 1);
    if (prompt == NULL)
		return (ft_free(&hostname), ft_free(&path), NULL);
    ft_strlcat(prompt, user, sum_len);
    ft_strlcat(prompt, "@", sum_len);
    ft_strlcat(prompt, hostname, sum_len);
    ft_strlcat(prompt, ":", sum_len);
    ft_strlcat(prompt, path, sum_len);
    ft_strlcat(prompt, "$>", sum_len);
	ft_free(&hostname);
    ft_free(&path);
    return (prompt);
}
/* @brief it get the current user, current path and the hostname to get 
	a prompt mimicing bash
	it takes the information for envriomental variables if they are
	not available it puts a placeholder.
	@return it returns NULL in case of error or the prompt that mimics bash:
	"<USER>@<HOSTNAME>:~/<PATH>$ "
	*/
char	*get_prompt(void)
{
	int	fd;
	char *user;
	char *path;
	char *hostname;
	int bytes_read;

	fd = 0;
	bytes_read = 0;
	user = NULL;
	path = NULL;
	user = getenv("USER");
	if (user == NULL)
		user = "UNKNOWN_USER";
	path = getcwd(NULL, 0);
	if (path == NULL)
		path = "UNKNOWN_PATH";	
	fd = open("/etc/hostname", O_RDONLY);
	if (fd == -1)
		hostname = ft_strdup("UNKNOWN_HOSTNAME");
	else
	{
		hostname = malloc(256);
		bytes_read = read(fd, hostname, sizeof(hostname) - 1);
		close(fd);
	}
	if (hostname == NULL)
		return (NULL);
	if (bytes_read > 0)
		hostname[bytes_read - 1] = '\0';
	return (join_everything(user, path, hostname));
}
