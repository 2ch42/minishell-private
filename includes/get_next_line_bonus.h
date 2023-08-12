/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junglee <junglee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 14:14:37 by junglee           #+#    #+#             */
/*   Updated: 2023/08/08 18:55:27 by junglee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H
# include <stdlib.h>
# include <unistd.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

typedef struct s_gnl_list
{
	char				*backup;
	int					fd;
	int					read_size;
	int					find;
	struct s_gnl_list	*next;
}	t_gnl_list;

t_gnl_list	*find_or_add(t_gnl_list **head, int fd);
void		gnl_delete_node(t_gnl_list **head, int fd);
char		*gnl_strjoin(const char *s1, const char *s2, int *malb);
size_t		gnl_strlen(const char *s);
char		*check_backup(t_gnl_list *lp, int *crack_malloc);

char		*get_next_line(int fd);
int			find_nl(t_gnl_list *cur_node, char *back_line);
char		*final_check(t_gnl_list **head, int fd, int *malb, char *line);
char		*sep_line(t_gnl_list *cur_node, int *malb);
char		*gnl_strlcpy(const char *src, size_t dstsize, int *malb);

#endif