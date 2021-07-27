/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 13:40:31 by twagner           #+#    #+#             */
/*   Updated: 2021/05/25 13:40:32 by twagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 32
# endif
# define ERROR -1
# define NORMAL_LINE 1
# define FINAL_LINE 0
# define ALL -2
# define TO_CLEAR ALL
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>

typedef struct s_list_fd
{
	int					fd;
	char				*content;
	struct s_list_fd	*next;
}						t_list_fd;

int		get_next_line(int fd, char **line);
int		ft_update_list_fd(t_list_fd **list, int fd, char c);
char	*ft_create_line(t_list_fd *lst, int fd, char c);
int		ft_fd_to_list(t_list_fd **list, int fd, char c);
char	*ft_strchr(const char *s, int c);
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
void	*ft_realloc(void *ptr, size_t size);
int		ft_lstclear(int to_clear, t_list_fd **lst);
int		ft_lstadd_new_back(t_list_fd **list, char *content, int fd);
char	*ft_substr(char const *s, unsigned int start, size_t len);

#endif
