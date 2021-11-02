/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkosaka <jkosaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 14:05:15 by jkosaka           #+#    #+#             */
/*   Updated: 2021/11/02 18:47:56 by jkosaka          ###   ########.fr       */
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

#include <fcntl.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

int  main(void)
{
    int     fd;
    int		fd02;
    char	*buff;
    char	*buff02;

    if ((fd = open("sample1.txt", O_RDONLY)) == -1)
    {
        printf("fopen error(%s)\n", strerror(errno));
        return (0);
    }
    fd = 0;
    // if ((fd02 = open("sample1.txt", O_RDONLY)) == -1)
    // {
    //     printf("fopen error(%s)\n", strerror(errno));
    //     return (0);
    // }
    while (1)
    {
        buff = get_next_line(fd);
        printf("answer:%s", buff);
        // free(buff);
        // buff02 = get_next_line(fd02);
        // printf("answer:%s", buff02);
        if (!buff)
        // if (!buff || !buff02)
            break;
    }
    close(fd);
    system("leaks a.out"); // メモリリークチェック
    return (0);
}