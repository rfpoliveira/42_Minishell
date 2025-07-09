/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpedrosa <rpedrosa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 11:01:45 by rpedrosa          #+#    #+#             */
/*   Updated: 2024/11/12 11:02:14 by rpedrosa         ###   ########.fr       */
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
			return (NULL);
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

char	*get_next_line(int fd)
{
	static char		*rest;
	char			*buff;
	char			*line;

	buff = malloc(BUFFER_SIZE + 1);
	if (!buff)
		return (NULL);
	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		r_free(&buff);
		r_free(&rest);
		return (NULL);
	}
	line = fill_buff(fd, buff, rest);
	r_free(&buff);
	if (!line)
	{
		r_free(&line);
		r_free(&rest);
		return (NULL);
	}
	rest = true_line(line);
	return (line);
}
/*
int	main(void)
{
	char *s = "h";
	int fd = open ("./tests/lines_around_10.txt", O_RDONLY);
	s = get_next_line(fd);
	while (s)
	{
		printf("%s", s);
		free(s);
		s = get_next_line(fd);
	}
	close(fd);
}*/
