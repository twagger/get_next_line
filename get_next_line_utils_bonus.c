/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 13:40:21 by twagner           #+#    #+#             */
/*   Updated: 2021/05/25 13:40:22 by twagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == c)
			return ((char *)s);
		++s;
	}
	if (c == 0 && s)
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
	new[0] = 0;
	ft_strlcat(new, ptr, size);
	free(ptr);
	return (new);
}

int	ft_lstclear(int fd, t_list_fd **lst)
{
	t_list_fd	*begin;
	t_list_fd	*next;
	t_list_fd	*previous;

	previous = NULL;
	begin = *lst;
	while (*lst)
	{
		next = (*lst)->next;
		if ((*lst)->fd == fd || (*lst)->fd == TO_CLEAR || fd == ALL)
		{
			if (*lst == begin)
				begin = next;
			free((*lst)->content);
			free(*lst);
			*lst = NULL;
			if (previous)
				previous->next = next;
		}
		if (*lst)
			previous = *lst;
		*lst = next;
	}
	*lst = begin;
	return (ERROR);
}

int	ft_lstadd_new_back(t_list_fd **list, char *content, int fd)
{
	t_list_fd	*new;
	t_list_fd	*begin;

	new = (t_list_fd *)malloc(sizeof(*new));
	if (!new)
		return (0);
	new->fd = fd;
	new->content = ft_substr(content, 0, ft_strchr(content, 0) - content);
	if (!new->content)
	{
		free(new);
		return (0);
	}
	new->next = NULL;
	if (*list)
	{
		begin = *list;
		while ((*list)->next)
			*list = (*list)->next;
		(*list)->next = new;
		*list = begin;
	}
	else
		*list = new;
	return (1);
}
