/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkosaka <jkosaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 14:05:15 by jkosaka           #+#    #+#             */
/*   Updated: 2021/11/04 18:16:30 by jkosaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void	*free_one(char **s)
{
	free(*s);
	return (*s = NULL);
}

static void	*free_all(char **s1, char **s2)
{
	free_one(s1);
	free_one(s2);
	return (NULL);
}

static char	*join_words(char **s1, const char *s2)
{
	char	*ret;
	size_t	s1_len;
	size_t	s2_len;
	size_t	total_len;

	if (!(*s1) || !s2)
		return (free_one(s1));
	s1_len = ft_strlen(*s1);
	s2_len = ft_strlen(s2);
	total_len = s1_len + s2_len;
	ret = (char *)malloc(sizeof(char) * (total_len + 1));
	if (!ret)
		return (free_one(s1));
	ft_strlcpy(ret, *s1, s1_len + 1);
	ft_strlcpy(ret + s1_len, s2, total_len + 1);
	free_one(s1);
	return (ret);
}

static char	*get_one_line(char **save, size_t len)
{
	char	*ret;
	char	*temp;

	if (!len || !(*save))
		return (free_one(&(*save)));
	ret = (char *)malloc(sizeof(char) * (len + 1));
	if (!ret)
		return (free_one(&(*save)));
	ft_strlcpy(ret, *save, len + 1);
	temp = NULL;
	if (*((*save) + len))
		temp = ft_strdup((*save) + len);
	free(*save);
	*save = temp;
	return (ret);
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
		if (read_bytes == -1)
			return (free_all(&save[fd], &buff));
		buff[read_bytes] = '\0';
		save[fd] = join_words(&save[fd], buff);
	}
	free_one(&buff);
	if (!read_bytes)
		return (get_one_line(&save[fd], ft_strlen(save[fd])));
	return (get_one_line(&save[fd], ft_strchr(save[fd], '\n') - save[fd] + 1));
}
