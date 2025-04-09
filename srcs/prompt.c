/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpedrosa <rpedrosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 16:54:00 by rpedrosa          #+#    #+#             */
/*   Updated: 2025/04/09 14:58:07 by rpedrosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

static void parse_path(char *user, char **path)
{
	int		check_len;
	char	*temp;

	check_len = 0;
	check_len = 6 + ft_strlen(user);
	temp = ft_calloc(check_len, sizeof(char));
	ft_strlcat(temp, "/home/", check_len);
	ft_strlcat(temp, user, check_len);
	if (ft_strncmp(*path, temp, check_len - 1) == 0)
	{
		free(temp);
		temp = ft_strdup(*path + check_len);
		free(*path);
		check_len = ft_strlen(temp) + 2;
		*path = ft_calloc(check_len, sizeof(char));
		(*path)[0] = '~';
		ft_strlcat(*path, temp, check_len);
	}
	ft_free(&temp);
}

static char    *join_everything(char *user, char *path, char *hostname)
{
    char    *prompt;
    int     sum_len;

    sum_len = 0;
	parse_path(user, &path);
    sum_len = ft_strlen(user) + ft_strlen(path) + ft_strlen(hostname) + 5;
    prompt = ft_calloc(sum_len, 1);
    if (prompt == NULL)
        return (NULL);
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
	if (bytes_read > 0)
		hostname[bytes_read - 1] = '\0';
	return (join_everything(user, path, hostname));
}
