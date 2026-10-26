/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manand <manand@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/08 11:43:31 by manand            #+#    #+#             */
/*   Updated: 2026/10/26 19:08:12 by manand           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//cc -Wall -Wextra -Werror -D 
// BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c main.c

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strchr(const char *s, int c)
{
	size_t	i;

	if (!s)
		return (NULL);
	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return ((char *)(s + i));
		i++;
	}
	if (s[i] == (char)c)
		return ((char *)(s + i));
	return (NULL);
}

char	*ft_strdup(const char *s1)
{
	size_t	i;
	char	*dest;

	i = ft_strlen(s1);
	dest = (char *)malloc(sizeof(char) * (i + 1));
	if (!dest)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		dest[i] = s1[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

int	ft_grow(t_str *s, size_t need)
{
	char	*new;
	size_t	i;

	while (need + 1 > s->cap)
		s->cap *= 2;
	new = malloc(s->cap);
	if (!new)
	{
		free(s->data);
		s->data = NULL;
		return (0);
	}
	i = 0;
	while (i < s->len)
	{
		new[i] = s->data[i];
		i++;
	}
	new[i] = '\0';
	free(s->data);
	s->data = new;
	return (1);
}

int	ft_append(t_str *s, const char *buf, size_t n)
{
	size_t	i;

	if (s->len + n + 1 > s->cap && !ft_grow(s, s->len + n))
		return (0);
	i = 0;
	while (i < n)
		s->data[s->len++] = buf[i++];
	s->data[s->len] = '\0';
	return (1);
}
