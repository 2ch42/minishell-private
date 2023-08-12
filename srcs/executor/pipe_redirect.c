/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_redirect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junglee <junglee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 19:44:39 by junglee           #+#    #+#             */
/*   Updated: 2023/08/04 16:39:30 by junglee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "wrapping.h"
#include <unistd.h>

static void	redirect_in(int pipe_fd[2])
{
	close_s(pipe_fd[READ]);
	dup2_s(pipe_fd[WRITE], STDOUT_FILENO);
}

static void	redirect_mid(int read_pipe[2], int write_pipe[2])
{
	dup2_s(read_pipe[READ], STDIN_FILENO);
	close_s(write_pipe[READ]);
	dup2_s(write_pipe[WRITE], STDOUT_FILENO);
}

static void	redirect_out(int pipe_fd[2])
{
	dup2_s(pipe_fd[READ], STDIN_FILENO);
}

void	redirect_pipe_children(int pipe_fd[2][2], int i, int pipe_num)
{
	int	read;
	int	write;

	set_pipe_direction(i, &read, &write);
	if (i == 0)
		redirect_in(pipe_fd[write]);
	else if (i == pipe_num)
		redirect_out(pipe_fd[read]);
	else
		redirect_mid(pipe_fd[read], pipe_fd[write]);
}

void	set_pipe_direction(int i, int *read, int *write)
{
	if (i % 2 == 0)
	{
		*read = 1;
		*write = 0;
	}
	else
	{
		*read = 0;
		*write = 1;
	}
}
