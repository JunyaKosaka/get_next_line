/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkosaka <jkosaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 14:05:15 by jkosaka           #+#    #+#             */
/*   Updated: 2021/10/29 14:32:00 by jkosaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

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
	char	*pt;

	ret = (char *)malloc(sizeof(char) * (len + 1));
	pt = ret;
	if (**save == '\0')
		return (NULL);
	ft_strlcpy(ret, *save, len + 1);
	*save += len + 1;
	return (ret);
}

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	ret;
	size_t	dst_len;
	size_t	src_len;

	dst_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	ret = dst_len + src_len;
	if (dstsize < dst_len + 1)
		return (dstsize + src_len);
	ft_strlcpy(dst + dst_len, src, dstsize - dst_len);
	return (ret);
}

void *word_join(char **s1, char *s2)
{
	char	*new;
	size_t	s1_len;
	size_t	s2_len;
	size_t	size;

	if (!(*s1))
		*s1 = "";
	s1_len = ft_strlen(*s1);
	s2_len = ft_strlen(s2);
	size = s1_len + s2_len;
	new = (char *)malloc(sizeof(char) * (size + 1));
	if (!new)
	{
		free(*s1);
		free(s2);
		return (NULL);
	}
	ft_strlcpy(new, *s1, s1_len + 1);
	ft_strlcpy(new + s1_len, s2, size + 1);
	free(s2);
	*s1 = new;
	return (*s1);
}

char	*get_next_line(int fd)
{
	static char	*save[FOPEN_MAX] = {NULL};
	char		*buff;
	int			read_bytes;

	if (0 < fd || fd >= FOPEN_MAX || BUFFER_SIZE <= 0)
		return (NULL);
	if (save[fd] && ft_strchr(save[fd], '\n'))
		return (get_one_line(&save[fd], ft_strchr(save[fd], '\n') - save[fd] + 1));
	while (1)
	{
		buff = (char *)malloc(sizeof(char) * ((size_t)BUFFER_SIZE + 1));
		if (!buff)
			return (NULL);
		read_bytes = read(fd, buff, BUFFER_SIZE);
		if (read_bytes <= 0)
		{
			free(buff);
			return (get_one_line(&(save[fd]), ft_strlen(save[fd])));
		}
		buff[read_bytes] = '\0';
		word_join(&save[fd], buff);
		// free(buff);
		if (save[fd] && ft_strchr(save[fd], '\n'))
			return (get_one_line(&save[fd], ft_strchr(save[fd], '\n') - save[fd] + 1));
	}
	return (NULL);
}

#include <fcntl.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

// int	main(void)
// {
//     int 	fd;
// 	// int		fd02;
//     char 	*buff;
//     // char 	*buff02;

//     if ((fd = open("sample4.txt", O_RDONLY)) == -1)
//     {
// 		printf("fopen error(%s)\n", strerror(errno));
//         return (0);
//     }
// 	fd = 0;
//     // if ((fd02 = open("sample5.txt", O_RDONLY)) == -1)
//     // {
// 	// 	printf("fopen error(%s)\n", strerror(errno));
//     //     return (0);
//     // }
// 	while ((buff = get_next_line(fd)))
//     {
// 		printf("answer:%s\n", buff);
// 		// printf("answer:%s\n", buff02);
//     }
//     close(fd);
// 	// system("leaks a.out"); // メモリリークチェック
//     return (0);
// }
