/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junglee <junglee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 16:32:05 by junglee           #+#    #+#             */
/*   Updated: 2023/08/09 20:49:12 by junglee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "utils.h"
#include <unistd.h>

int	here_doc_count(t_tk_list *tk_list)
{
	int		heredoc_num;
	t_tk	*head;

	heredoc_num = 0;
	head = tk_list->head;
	while (head)
	{
		if (head->tktype == heredoc)
			heredoc_num++;
		head = head->next;
	}
	return (heredoc_num);
}

void	here_doc_delete(t_heredoc_info *here_doc_info, int here_doc_num)
{
	int	i;

	i = 0;
	while (i < here_doc_num)
	{
		unlink(here_doc_info[i].file_name);
		i++;
	}
	free(here_doc_info);
}

void	buf_nl_clear(char *buf)
{
	int	i;

	i = 0;
	while (buf[i])
		i++;
	if (buf[i - 1] == '\n')
		buf[i - 1] = 0;
}

char	*get_here_doc_file_name(void)
{
	static unsigned int	file_num;
	char				*file_name;
	char				*temp;

	file_name = 0;
	while (1)
	{
		if (file_name != 0)
			free(file_name);
		file_name = ft_itoa(file_num);
		temp = file_name;
		file_name = ft_strjoin(".heredoc_temp_file", file_name);
		free(temp);
		if (access(file_name, F_OK) != 0)
			break ;
		file_num++;
	}
	file_num++;
	return (file_name);
}

void	heredoc_file_change(t_tk_list *tk_list, t_heredoc_info *here_doc_info)
{
	t_tk	*head;
	int		i;

	head = tk_list->head;
	i = 0;
	while (head)
	{
		if (head->tktype == heredoc)
		{
			here_doc_info[i].file_name = get_here_doc_file_name();
			i++;
		}
		head = head->next;
	}
}
