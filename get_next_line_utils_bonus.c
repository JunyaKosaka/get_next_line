/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkosaka <jkosaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 14:09:08 by jkosaka           #+#    #+#             */
/*   Updated: 2021/11/02 18:34:40 by jkosaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	ft_strlen(const char *s)
{
	size_t	ind;

	ind = 0;
	while (s[ind])
		ind++;
	return (ind);
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

	if (!s1)
		return (NULL);
	len = ft_strlen(s1);
	ret = (char *)malloc(sizeof(char) * (len + 1));
	if (!ret)
		return (NULL);
	ft_strlcpy(ret, s1, len + 1);
	return (ret);
}

char	*join_words(char **s1, const char *s2)
{
	char	*ret;
	size_t	size;

	if (!(*s1) || !s2)
	{
		free(*s1);
		*s1 = NULL;
		return (NULL);
	}
	size = ft_strlen(*s1) + ft_strlen(s2);
	ret = (char *)malloc(sizeof(char) * (size + 1));
	if (!ret)
	{
		free(*s1);
		*s1 = NULL;
		return (NULL);
	}
	ft_strlcpy(ret, *s1, ft_strlen(*s1) + 1);
	ft_strlcpy(ret + ft_strlen(*s1), s2, size + 1);
	free(*s1);
	*s1 = NULL;
	return (ret);
}