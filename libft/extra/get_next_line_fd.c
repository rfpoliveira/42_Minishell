/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpedrosa <rpedrosa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 09:46:00 by rpedrosa          #+#    #+#             */
/*   Updated: 2024/11/22 09:46:06 by rpedrosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "extra.h"

static char	*fill_buff(int fd, char *buff, char *rest)
{
	char	*tmp;
	ssize_t	i;

	i = 1;
	while (i > 0)
	{
		i = read(fd, buff, BUFFER_SIZE);
		if (i == -1)
		{
			free(rest);
			return (NULL);
		}
		else if (i == 0)
			break ;
		buff[i] = '\0';
		if (!rest)
			rest = ft_strdup("");
		tmp = rest;
		rest = ft_strjoin(tmp, buff);
		r_free(&tmp);
		if (ft_strchr(buff, '\n'))
			break ;
	}
	return (rest);
}

static char	*true_line(char	*line)
{
	size_t	i;
	char	*rest;

	i = 0;
	while (line[i] != '\n' && line[i])
		i++;
	if (!line[i] || !line[1])
		return (NULL);
	rest = ft_substr(line, i + 1, ft_strlen(line) - i);
	if (!*rest)
		r_free(&rest);
	line[i + 1] = '\0';
	return (rest);
}

char	*get_next_line_fd(int fd)
{
	static char		*rest[1024];
	char			*buff;
	char			*line;

	buff = malloc(BUFFER_SIZE + 1);
	if (!buff)
		return (NULL);
	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		r_free(&buff);
		r_free(&rest[fd]);
		return (NULL);
	}
	line = fill_buff(fd, buff, rest[fd]);
	r_free(&buff);
	if (!line)
	{
		r_free(&line);
		r_free(&rest[fd]);
		return (NULL);
	}
	rest[fd] = true_line(line);
	return (line);
}
/*
int	main(void)
{
	int i = 0;
	char *s = "h";
	int fd = open ("./tests/lines_around_10.txt", O_RDONLY);
	while (s)
	{
		s = get_next_line_fd(fd);
		printf("%s", s);
		i++;
		free(s);
	}
	close(fd);
}*/
