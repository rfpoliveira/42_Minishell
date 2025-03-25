/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpedrosa <rpedrosa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 16:54:00 by rpedrosa          #+#    #+#             */
/*   Updated: 2025/03/25 17:38:13 by rpedrosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

static char    *join_everything(char *user, char *path, char *hostname)
{
    char    *prompt;
    int     sum_len;

    sum_len = 0;
    sum_len = ft_strlen(user) + ft_strlen(path) + ft_strlen(hostname) + 5;
    printf("path: %s \nuser: %s \nhostname: %s \nsum_len: %i\n", path, user, hostname, sum_len);
    prompt = ft_calloc(sum_len, 1);
    if (prompt == NULL)
        return (NULL);
    ft_strlcat(prompt, user, sum_len);
    ft_strlcat(prompt, "@", sum_len);
    ft_strlcat(prompt, hostname, sum_len);
    ft_strlcat(prompt, ":", sum_len);
    ft_strlcat(prompt, path, sum_len);
    ft_strlcat(prompt, "$ ", sum_len);
    ft_free(&path);
    return (prompt);
}

char	*get_prompt(void)
{
	int	fd;
	char *user;
	char *path;
	char hostname[256];
	int bytes_read;

	fd = 0;
	bytes_read = 0;
	user = NULL;
	path = NULL;
	user = getenv("USER");
	path = getcwd(NULL, 0);
	fd = open("/etc/hostname", O_RDONLY);
	if (fd < 0)
	{
		fd = open("/etc/HOSTNAME", O_RDONLY);
		if (fd < 0)
			return (NULL);
	}
	bytes_read = read(fd, hostname, sizeof(hostname) - 1);
	close(fd);
	if (bytes_read > 0)
		hostname[bytes_read - 1] = '\0';
	return (join_everything(user, path, hostname));
}