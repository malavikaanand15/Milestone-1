/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manand <manand@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/08 12:42:57 by manand            #+#    #+#             */
/*   Updated: 2026/10/26 19:17:10 by manand           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_line(char *buffer)
{
	char	*line;
	size_t	i;

	i = 0;
	if (!buffer || !buffer[i])
		return (NULL);
	while (buffer[i] && (buffer[i] != '\n'))
		i++;
	line = malloc(i + 2);
	if (!line)
		return (NULL);
	i = 0;
	while (buffer[i] && (buffer[i] != '\n'))
	{
		line[i] = buffer[i];
		i++;
	}
	if (buffer[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

char	*ft_next(char *buffer)
{
	size_t	i;
	size_t	j;
	char	*next_line;

	i = 0;
	while (buffer && buffer[i] && buffer[i] != '\n')
		i++;
	if (!buffer || !buffer[i])
	{
		free(buffer);
		return (NULL);
	}
	next_line = malloc(ft_strlen(buffer) - i);
	if (next_line)
	{
		j = 0;
		while (buffer[++i])
			next_line[j++] = buffer[i];
		next_line[j] = '\0';
	}
	free(buffer);
	return (next_line);
}

static int	ft_read_loop(int fd, t_str *s, char *buf)
{
	int	n;

	n = 1;
	while (n > 0)
	{
		n = read(fd, buf, BUFFER_SIZE);
		if (n < 0)
			return (0);
		buf[n] = '\0';
		if (!ft_append(s, buf, n))
			return (0);
		if (ft_strchr(buf, '\n'))
			break ;
	}
	return (1);
}

char	*ft_read_line(int fd, char *line)
{
	t_str	s;
	char	*buf;

	if (!line)
		line = ft_strdup("");
	if (!line || ft_strchr(line, '\n'))
		return (line);
	buf = malloc(BUFFER_SIZE + 1);
	if (!buf)
	{
		free(line);
		return (NULL);
	}
	s.data = line;
	s.len = ft_strlen(line);
	s.cap = s.len + 1;
	if (!ft_read_loop(fd, &s, buf))
	{
		free(s.data);
		free(buf);
		return (NULL);
	}
	free(buf);
	return (s.data);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = ft_read_line(fd, buffer);
	if (!buffer)
		return (NULL);
	line = ft_line(buffer);
	buffer = ft_next(buffer);
	return (line);
}
