/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/23 14:29:40 by twagner           #+#    #+#             */
/*   Updated: 2021/05/23 14:29:44 by twagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strcpy(char *dst, const char *src)
{
	size_t	i;

	i = -1;
	while (src[++i])
		dst[i] = src[i];
	dst[i] = '\0';
	return (dst);
}

char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		++s;
	}
	if (c == 0)
		return ((char *)s);
	return (NULL);
}

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	s_len;
	size_t	d_len;
	size_t	i;
	size_t	result;

	i = 0;
	s_len = ft_strchr(src, 0) - src;
	d_len = ft_strchr(dst, 0) - dst;
	if (dstsize >= d_len)
		result = s_len + d_len;
	else
		result = s_len + dstsize;
	if (dstsize > d_len)
	{
		while (src[i] && d_len < dstsize - 1)
		{
			dst[d_len] = src[i];
			++d_len;
			++i;
		}
	}
	dst[d_len] = '\0';
	return (result);
}

void	*ft_realloc(void *ptr, size_t size)
{
	char	*new;

	if (!ptr)
	{
		new = (char *)malloc(sizeof(*new) * size);
		if (!new)
			return (ptr);
		return (new);
	}
	if (size == 0 && ptr)
	{
		new = (char *)malloc(sizeof(*new));
		if (!new)
			return (ptr);
		new[0] = 0;
		return (new);
	}
	new = (char *)malloc(sizeof(*new) * size);
	if (!new)
		return (ptr);
	new = ft_strcpy(new, ptr);
	free(ptr);
	return (new);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*res;
	size_t	i;
	size_t	slen;
	size_t	rlen;

	if (!s)
		return (NULL);
	slen = ft_strchr(s, 0) - s;
	if (start >= slen)
		rlen = 0;
	else if (start + len > slen)
		rlen = slen - start;
	else
		rlen = len;
	res = (char *)malloc(sizeof(*res) * (rlen + 1));
	if (!res)
		return (NULL);
	i = 0;
	while (s[start + i] && i < rlen)
	{
		res[i] = s[start + i];
		++i;
	}
	res[i] = '\0';
	return (res);
}
