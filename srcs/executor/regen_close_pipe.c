/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   regen_close_pipe.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junglee <junglee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 19:42:05 by junglee           #+#    #+#             */
/*   Updated: 2023/08/08 18:44:05 by junglee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "wrapping.h"

static void	close_in(int pipe_fd[2])
{
	close_s(pipe_fd[WRITE]);
}

static void	close_mid(int read_pipe[2], int write_pipe[2])
{
	close_s(read_pipe[READ]);
	close_s(write_pipe[WRITE]);
}

static void	close_out(int pipe_fd[2])
{
	close_s(pipe_fd[READ]);
}

void	regen_pipe(int pipe_fd[2][2], int i, int pipe_num)
{
	int	read;
	int	write;

	set_pipe_direction(i, &read, &write);
	if (i == 0)
		pipe_s(pipe_fd[0]);
	else if (i == pipe_num)
		return ;
	else
	{
		if (i % 2 == 0)
			pipe_s(pipe_fd[write]);
		else
			pipe_s(pipe_fd[write]);
	}
}

void	close_pipe(int pipe_fd[2][2], int i, int pipe_num)
{
	int	read;
	int	write;

	set_pipe_direction(i, &read, &write);
	if (i == 0)
		close_in(pipe_fd[write]);
	else if (i == pipe_num)
		close_out(pipe_fd[read]);
	else
		close_mid(pipe_fd[read], pipe_fd[write]);
}
