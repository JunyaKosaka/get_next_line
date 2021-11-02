/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkosaka <jkosaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 14:05:15 by jkosaka           #+#    #+#             */
/*   Updated: 2021/11/02 18:37:29 by jkosaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strchr(const char *s, int c)
{
	while (*s && *s != (char)c)
		s++;
	if (*s == (char)c)
		return ((char *)s);
	return (NULL);
}

static char	*get_one_line(char **save, size_t len)
{
	char	*ret;
	char	*temp;

	if (!len || !(*save))
	{
		free(*save);
		*save = NULL;
		return (NULL);
	}
	ret = (char *)malloc(sizeof(char) * (len + 1));
	if (!ret)
	{
		free(*save);
		*save = NULL;
		return (NULL);
	}
	ft_strlcpy(ret, *save, len + 1);
	temp = ft_strdup((*save) + len);
	free(*save);
	*save = temp;
	return (ret);
}

static size_t	get_len(const char *s, char c)
{
	return (ft_strchr(s, c) - s + 1);
}

static void	*free_all(char **s1, char **s2)
{
	free(*s1);
	*s1 = NULL;
	free(*s2);
	*s2 = NULL;
	return (NULL);
}

char	*get_next_line(int fd)
{
	static char	*save[FD_MAX] = {NULL};
	char		*buff;
	int			read_bytes;

	if (fd < 0 || FD_MAX <= fd || BUFFER_SIZE <= 0)
		return (NULL);
	buff = (char *)malloc(sizeof(char) * ((size_t)BUFFER_SIZE + 1));
	if (!buff)
		return (free_all(&save[fd], &buff));
	if (!save[fd])
		save[fd] = ft_strdup("");
	read_bytes = 1;
	while (read_bytes && !ft_strchr(save[fd], '\n'))
	{
		read_bytes = read(fd, buff, BUFFER_SIZE);
		if (read_bytes == -1 || (!read_bytes && !ft_strlen(save[fd])))
			return (free_all(&save[fd], &buff));
		buff[read_bytes] = '\0';
		save[fd] = join_words(&save[fd], buff);
	}
	free(buff);
	buff = NULL;
	if (!read_bytes)
		return (get_one_line(&save[fd], ft_strlen(save[fd])));
	return (get_one_line(&save[fd], get_len(save[fd], '\n')));
}
