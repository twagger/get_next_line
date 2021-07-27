/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 13:40:09 by twagner           #+#    #+#             */
/*   Updated: 2021/05/25 13:40:15 by twagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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
	while (i < rlen && s[start + i])
	{
		res[i] = s[start + i];
		++i;
	}
	res[i] = '\0';
	return (res);
}

int	ft_update_list_fd(t_list_fd **list, int fd, char c)
{
	t_list_fd	*begin;

	begin = *list;
	while (*list)
	{
		if ((*list)->fd == fd)
		{
			if (ft_strchr((*list)->content, c))
			{
				if (!ft_lstadd_new_back(list, \
					ft_strchr((*list)->content, c) + 1, fd))
					return (0);
				(*list)->fd = TO_CLEAR;
				*list = begin;
				return (1);
			}
			(*list)->fd = TO_CLEAR;
		}
		*list = (*list)->next;
	}
	*list = begin;
	return (1);
}

char	*ft_create_line(t_list_fd *lst, int fd, char c)
{
	char	*line;
	size_t	len;
	size_t	clen;

	line = (char *)malloc(sizeof(*line));
	if (!line)
		return (NULL);
	line[0] = 0;
	while (lst)
	{
		if (lst->fd == fd)
		{
			if (ft_strchr(lst->content, c))
				clen = ft_strchr(lst->content, c) - lst->content;
			else
				clen = ft_strchr(lst->content, 0) - lst->content;
			len = (ft_strchr(line, 0) - line) + clen + 1;
			line = ft_realloc(line, len);
			ft_strlcat(line, lst->content, len);
		}
		lst = lst->next;
	}
	return (line);
}

int	ft_fd_to_list(t_list_fd **list, int fd, char c)
{
	int		ret;
	char	*buf;

	buf = (char *)malloc(sizeof(*buf) * (BUFFER_SIZE + 1));
	if (!buf)
		return (ERROR);
	while (1)
	{
		ret = read(fd, buf, BUFFER_SIZE);
		if (ret == 0 || ret == -1)
		{	
			free(buf);
			return (ret);
		}
		buf[ret] = '\0';
		if (!ft_lstadd_new_back(list, buf, fd))
		{
			free(buf);
			return (ERROR);
		}
		if (ft_strchr(buf, c))
			break ;
	}
	free(buf);
	return (NORMAL_LINE);
}

int	get_next_line(int fd, char **line)
{
	static t_list_fd	*list = NULL;
	t_list_fd			*begin;
	int					result;

	if (fd < 0 || !line || BUFFER_SIZE <= 0)
		return (ERROR);
	result = -2;
	begin = list;
	while (list)
	{
		if (list->fd == fd && ft_strchr(list->content, '\n'))
			result = NORMAL_LINE;
		list = list->next;
	}
	list = begin;
	if (!list || result == -2)
		result = ft_fd_to_list(&list, fd, '\n');
	if (result == ERROR)
		return (ft_lstclear(fd, &list));
	*line = ft_create_line(list, fd, '\n');
	if (!*line || !ft_update_list_fd(&list, fd, '\n'))
		return (ft_lstclear(ALL, &list));
	if (result == FINAL_LINE)
		ft_lstclear(fd, &list);
	return (result);
}
