/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkosaka <jkosaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 16:32:22 by jkosaka           #+#    #+#             */
/*   Updated: 2021/11/06 17:54:21 by jkosaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include "get_next_line.h"

int  main(void)
{
    int     fd;
    int        fd02;
    int        fd03;
    char     *buff;
    char     *buff02;
    char     *buff03;

    if ((fd = open("sample6.txt", O_RDONLY)) == -1)
    {
        printf("fopen error(%s)\n", strerror(errno));
        return (0);
    }
    // fd = 0;
    // if ((fd02 = open("sample1.txt", O_RDONLY)) == -1)
    // {
    //     printf("fopen error(%s)\n", strerror(errno));
    //     return (0);
    // }
    // if ((fd03 = open("sample2.txt", O_RDONLY)) == -1)
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
        // buff03 = get_next_line(fd03);
        // printf("answer:%s", buff03);
        if (!buff)
            break;
        // if (!buff || !buff02)
		free(buff);
		// free(buff02);
		// free(buff03);
    }
    close(fd);
	close(fd02);
	close(fd03);
    system("leaks a.out");
    return (0);
}
