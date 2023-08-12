/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junglee <junglee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 16:34:47 by junglee           #+#    #+#             */
/*   Updated: 2023/08/09 20:41:16 by junglee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "wrapping.h"
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include "get_next_line_bonus.h"

void	redirect_left(const char *file_path, int *fd, int *file_status)
{
	if (access_s(file_path, F_OK) != 0)
	{
		file_not_found_err(file_path);
		(*file_status)++;
		return ;
	}
	if (access_s(file_path, R_OK) != 0)
	{
		permission_err(file_path);
		(*file_status)++;
		return ;
	}
	(*fd) = open_s(file_path, O_RDONLY);
	dup2_s((*fd), STDIN_FILENO);
}

void	redirect_right(const char *file_path, int *fd, int *file_status)
{
	if (access_s(file_path, F_OK) != 0)
		(*fd) = open_s(file_path, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	else
	{
		if (access_s(file_path, W_OK) != 0)
		{
			permission_err(file_path);
			(*file_status)++;
			return ;
		}
		(*fd) = open_s(file_path, O_WRONLY | O_TRUNC);
	}
	dup2_s((*fd), STDOUT_FILENO);
}

void	here_doc(const char *delimter, t_heredoc_info *here_doc_info)
{
	char	*buf;
	int		temp_fd;

	here_doc_info->fd = open_s(here_doc_info->file_name, \
						O_WRONLY | O_CREAT | O_TRUNC, 0644);
	temp_fd = here_doc_info->fd;
	write(1, "> ", 2);
	buf = get_next_line(0);
	if (buf == 0)
		return ;
	buf_nl_clear(buf);
	while (ft_strcmp(buf, delimter))
	{
		write(temp_fd, buf, ft_strlen(buf));
		write(temp_fd, "\n", 1);
		free(buf);
		write(1, "> ", 2);
		buf = get_next_line(0);
		if (buf == 0)
			return ;
		buf_nl_clear(buf);
	}
	free(buf);
}

void	redirect_append(const char *file_path, int *fd, int *file_status)
{
	if (access_s(file_path, F_OK) != 0)
		(*fd) = open_s(file_path, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	else
	{
		if (access_s(file_path, W_OK) != 0)
		{
			permission_err(file_path);
			(*file_status)++;
			return ;
		}
		(*fd) = open_s(file_path, O_WRONLY | O_APPEND);
	}
	dup2_s((*fd), STDOUT_FILENO);
}
