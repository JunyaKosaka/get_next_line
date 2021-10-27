/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkosaka <jkosaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 14:09:08 by jkosaka           #+#    #+#             */
/*   Updated: 2021/10/26 09:36:17 by jkosaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void	write_fd(char **s, int fd, size_t len)
{
	write(fd, *s, len);
	*s += len;
}

void	ft_putstr_fd(char *s, int fd)
{
	size_t	len;

	if (!s)
		return ;
	len = ft_strlen(s);
	write_fd(&s, fd, len % INT_MAX);
	len /= INT_MAX;
	while (len--)
		write_fd(&s, fd, INT_MAX);
}

size_t	ft_strlen(const char *s)
{
	size_t	ind;

	ind = 0;
	while (s[ind])
		ind++;
	return (ind);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ret;
	size_t	s1_len;
	size_t	s2_len;
	size_t	size;

	if (!s1 || !s2)
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	size = s1_len + s2_len;
	ret = (char *)malloc(sizeof(char) * (size + 1));
	if (!ret)
		return (NULL);
	ft_strlcpy(ret, s1, s1_len + 1);
	ft_strlcpy(ret + s1_len, s2, size + 1);
	return (ret);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	ret;

	ret = ft_strlen(src);
	if (!dstsize)
		return (ret);
	dstsize -= 1;
	while (*src && dstsize-- > 0)
		*dst++ = *src++;
	*dst = '\0';
	return (ret);
}

char	*ft_strdup(const char *s1)
{
	char	*ret;
	size_t	len;

	len = ft_strlen(s1);
	ret = (char *)malloc(sizeof(char) * (len + 1));
	if (!ret)
		return (NULL);
	ft_strlcpy(ret, s1, len + 1);
	return (ret);
}