/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wrapping_func2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junglee <junglee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 16:44:51 by junglee           #+#    #+#             */
/*   Updated: 2023/08/05 20:42:42 by junglee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wrapping.h"
#include "executor.h"
#include <fcntl.h>
#include <unistd.h>

int	open_s(const char *path, int oflag, ...)
{
	int	re;

	re = open(path, oflag);
	if (re < 0)
		exit_error("minishell: open error", 1);
	return (re);
}

void	pipe_s(int pipe_fd[2])
{
	if (pipe(pipe_fd) == -1)
		exit_error("pipex: pipe error", 1);
}

void	close_s(int pipe_fd)
{
	if (close(pipe_fd) == -1)
		exit_error("piepx: close error", 1);
}

void	dup2_s(int fd1, int fd2)
{
	if (dup2(fd1, fd2) == -1)
		exit_error("piepx: dup2 error", 1);
}

pid_t	fork_s(void)
{
	pid_t	re;

	re = fork();
	if (re == -1)
		exit_error("minishell: fork error", 1);
	return (re);
}
