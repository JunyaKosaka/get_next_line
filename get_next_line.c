/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkosaka <jkosaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 14:05:15 by jkosaka           #+#    #+#             */
/*   Updated: 2021/11/04 18:15:20 by jkosaka          ###   ########.fr       */
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

// #include <fcntl.h>
// #include <sys/types.h>
// #include <sys/uio.h>
// #include <unistd.h>
// #include <errno.h>
// #include <string.h>
// #include <stdlib.h>

// int  main(void)
// {
//     int     fd;
//     int        fd02;
//     int        fd03;
//     char     *buff;
//     char     *buff02;
//     char     *buff03;

//     if ((fd = open("sample6.txt", O_RDONLY)) == -1)
//     {
//         printf("fopen error(%s)\n", strerror(errno));
//         return (0);
//     }
//     // fd = 0;
//     if ((fd02 = open("sample1.txt", O_RDONLY)) == -1)
//     {
//         printf("fopen error(%s)\n", strerror(errno));
//         return (0);
//     }
//     if ((fd03 = open("sample2.txt", O_RDONLY)) == -1)
//     {
//         printf("fopen error(%s)\n", strerror(errno));
//         return (0);
//     }
//     while (1)
//     {
//         buff = get_next_line(fd);
//         printf("answer:%s", buff);
//         // free(buff);
//         buff02 = get_next_line(fd02);
//         printf("answer:%s", buff02);
//         buff03 = get_next_line(fd03);
//         printf("answer:%s", buff03);
//         // if (!buff)
//         if (!buff || !buff02)
//             break;
// 		free(buff);
// 		free(buff02);
// 		free(buff03);
//     }
//     close(fd);
//     system("leaks a.out"); // メモリリークチェック
//     return (0);
// }
