/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkosaka <jkosaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 14:05:15 by jkosaka           #+#    #+#             */
/*   Updated: 2021/10/27 14:10:31 by jkosaka          ###   ########.fr       */
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

char	*get_one_line(char **data, size_t len)
{
	char	*ret;
	char	*pt;

	ret = (char *)malloc(sizeof(char) * (len + 1));
	pt = ret;
	if (**data == '\0')
		return (NULL);
	ret[0] = '\0';
	ft_strlcpy(ret, *data, len);
	*data += len + 1;
	return (ret);
}

char	*get_next_line(int fd)
{
	static char	*data = "";  // char *data[FD] = {NULL}; とする方法
	char		*buff;
	int			read_bytes;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (data && ft_strchr(data, '\n'))
		return (get_one_line(&data, ft_strchr(data, '\n') - data));
	while (1)
	{
		buff = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (!buff)
			return (NULL);
		read_bytes = read(fd, buff, BUFFER_SIZE);
		if (read_bytes <= 0)
		{
			free(buff);
			return (get_one_line(&data, ft_strlen(data)));
		}
		buff[read_bytes] = '\0';
		data = ft_strjoin(data, buff);
		free(buff);
		if (data && ft_strchr(data, '\n'))
			return (get_one_line(&data, ft_strchr(data, '\n') - data));
	}
}

#include <fcntl.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>

#define BUF_SIZE 1024

int	main(void)
{
    int 	fd;
    char 	*buff;

    if ((fd = open("test.txt", O_RDONLY)) == -1)
    {
        write(1, "error\n", 6);
        return (0);
    }
	while ((buff = get_next_line(fd)))
    {
		printf("answer:%s\n", buff);
    }
    close(fd);
    return (0);
}

	// buff = ft_strdup(""); //(char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	// ret = ft_strdup("");
	// if (data)
	// {
	// 	ret = ft_strdup(data);
	// 	free(data);
	// }
	// if (!buff)
	// 	return (NULL);  // ret のfreeは必要なのか
	// while (!(has_next(ret) && read_bytes)
	// {
	// 	read_bytes = read(fd, buff, BUFFER_SIZE); // 改行処理
	// 	if (read_bytes == -1)
	// 	{
	// 		free(buff);
	// 		return (NULL);// readに失敗してエラーが発生した時の処理
	// 	}
	// 	buff[read_bytes] = '\0';
	// 	data = ft_strjoin(data, buff);
	// 	if (ft_strchr(data, '\n'))
	// 		break ;
	// }
	// free(buff);
	// pt = ft_strchr(data, '\n');
	// ret = ft_substr(data, 0, pt - data);
	// data = pt;
	// if (*data == '\n')
	// 	data = pt + 1;
	// if (ret)
	// 	return (ret);
	// return (NULL);
	// if (!read_bytes)
	// 	return (NULL); // EOF