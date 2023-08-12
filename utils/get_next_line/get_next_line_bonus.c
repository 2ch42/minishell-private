/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junglee <junglee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 14:14:24 by junglee           #+#    #+#             */
/*   Updated: 2023/08/08 18:53:31 by junglee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*get_next_line(int fd)
{
	static t_gnl_list	*head;
	char				buf[BUFFER_SIZE + 1];
	int					malb;
	t_gnl_list			*cur_node;

	cur_node = find_or_add(&head, fd);
	if (!cur_node)
		return (0);
	malb = 0;
	if (cur_node->fd < 0 || BUFFER_SIZE < 1 || read(cur_node->fd, 0, 0) < 0)
	{
		gnl_delete_node(&head, fd);
		return (0);
	}
	while (cur_node->read_size > 0)
	{
		cur_node->read_size = read(cur_node->fd, buf, BUFFER_SIZE);
		buf[cur_node->read_size] = 0;
		cur_node->backup = gnl_strjoin(cur_node->backup, buf, &malb);
		if (!cur_node->backup)
			break ;
		if (find_nl(cur_node, cur_node->backup))
			return (final_check(&head, fd, &malb, sep_line(cur_node, &malb)));
	}
	return (final_check(&head, fd, &malb, check_backup(cur_node, &malb)));
}

char	*final_check(t_gnl_list **head, int fd, int *malb, char *line)
{
	t_gnl_list	*cur_node;

	cur_node = find_or_add(head, fd);
	if ((*malb) > 0 || cur_node->read_size < 0)
	{
		gnl_delete_node(head, fd);
		if (line)
			free(line);
		return (0);
	}
	if (cur_node->read_size == 0 && !find_nl(cur_node, line))
	{
		if (cur_node->read_size == 0 && cur_node->backup[0] == 0)
		{
			free(cur_node->backup);
			cur_node->backup = 0;
			gnl_delete_node(head, fd);
			return (0);
		}
		free(cur_node->backup);
		cur_node->backup = 0;
		gnl_delete_node(head, fd);
	}
	return (line);
}

char	*sep_line(t_gnl_list *cur_node, int *malb)
{
	char	*line;
	char	*tmp;
	size_t	backup_len;

	backup_len = gnl_strlen(cur_node->backup);
	line = gnl_strlcpy(cur_node->backup, cur_node->find + 2, malb);
	if (line == 0)
		return (0);
	tmp = gnl_strlcpy(cur_node->backup + cur_node->find + 1, \
	backup_len - cur_node->find, malb);
	if (tmp == 0)
	{
		free(line);
		return (0);
	}
	free(cur_node->backup);
	cur_node->backup = tmp;
	return (line);
}

char	*gnl_strlcpy(const char *src, size_t dstsize, int *malb)
{
	char	*str;
	size_t	i;
	size_t	s_len;

	i = 0;
	s_len = gnl_strlen(src);
	str = (char *)malloc(sizeof(char) * dstsize);
	if (!str)
	{
		(*malb)++;
		return (0);
	}
	while (i + 1 < dstsize && i < s_len)
	{
		str[i] = src[i];
		i++;
	}
	if (dstsize > 0)
		str[i] = 0;
	return (str);
}

int	find_nl(t_gnl_list *cur_node, char *back_line)
{
	int		i;

	i = 0;
	if (!back_line)
		return (0);
	while (back_line[i])
	{
		if (back_line[i] == '\n')
		{
			cur_node->find = i;
			return (1);
		}
		i++;
	}
	return (0);
}
