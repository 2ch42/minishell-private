/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junglee <junglee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 14:14:57 by junglee           #+#    #+#             */
/*   Updated: 2023/08/06 16:41:05 by junglee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

t_gnl_list	*find_or_add(t_gnl_list **head, int fd)
{
	t_gnl_list	*temp;
	t_gnl_list	*cur;

	cur = *head;
	while (cur)
	{
		if (cur->fd == fd)
			return (cur);
		cur = cur->next;
	}
	temp = (t_gnl_list *)malloc(sizeof(t_gnl_list));
	if (temp == 0)
		return (0);
	temp->fd = fd;
	temp->backup = 0;
	temp->find = -1;
	temp->read_size = BUFFER_SIZE;
	temp->next = *head;
	*head = temp;
	return (temp);
}

void	gnl_delete_node(t_gnl_list **head, int fd)
{
	t_gnl_list	*prev;
	t_gnl_list	*temp;

	prev = *head;
	if (prev->fd == fd)
	{
		temp = prev;
		*head = prev->next;
		if (temp->backup)
			free(temp->backup);
		free(temp);
		return ;
	}
	while (prev->next)
	{
		if (prev->next->fd == fd)
			break ;
		prev = prev->next;
	}
	temp = prev->next;
	prev->next = prev->next->next;
	if (temp->backup)
		free(temp->backup);
	free(temp);
}

char	*check_backup(t_gnl_list *cur_node, int *malb)
{
	char	*line;

	line = 0;
	if (cur_node->backup == 0)
		return (0);
	if (cur_node->read_size == 0)
	{
		if (cur_node->read_size == 0 && cur_node->backup[0] == 0)
			return (0);
		else if (cur_node->read_size == 0 && \
		!find_nl(cur_node, cur_node->backup))
			line = gnl_strlcpy(cur_node->backup, \
			gnl_strlen(cur_node->backup) + 1, malb);
		else
			line = sep_line(cur_node, malb);
	}
	return (line);
}

char	*gnl_strjoin(const char *s1, const char *s2, int *malb)
{
	int		i;
	int		j;
	char	*joinstr;
	char	*temp;

	i = 0;
	j = 0;
	temp = (char *)s1;
	joinstr = (char *)malloc(sizeof(char) * \
	(gnl_strlen(s1) + gnl_strlen(s2) + 1));
	if (!joinstr)
	{
		(*malb)++;
		free (temp);
		return (0);
	}
	while (s1 && s1[j])
		joinstr[i++] = s1[j++];
	j = 0;
	while (s2 && s2[j])
		joinstr[i++] = s2[j++];
	joinstr[i] = '\0';
	free(temp);
	return (joinstr);
}

size_t	gnl_strlen(const char *s)
{
	size_t	len;

	len = 0;
	if (!s)
		return (0);
	while (s[len])
		len++;
	return (len);
}
