/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junglee <junglee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 20:09:10 by junglee           #+#    #+#             */
/*   Updated: 2023/08/09 22:03:29 by junglee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include <errno.h>
#include <unistd.h>

static int	wait_signal(int *flag, int status);

int	wait_child_process(pid_t *pid_arr, int pipe_num)
{
	int	i;
	int	status;
	int	re_status;
	int	flag;

	i = 0;
	flag = 0;
	while (i <= pipe_num)
	{
		if (waitpid(pid_arr[i], &status, 0) == -1)
			exit_error("minishell: wait fail", 1);
		if (WIFEXITED(status))
			re_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			re_status = wait_signal(&flag, status);
		i++;
	}
	if (pipe_num != 0)
		free(pid_arr);
	return (re_status);
}

void	fd_close_and_word_free(int std_fd[2], char **word_arg)
{
	close(std_fd[IN]);
	close(std_fd[OUT]);
	free_arg(word_arg);
}

static int	wait_signal(int *flag, int status)
{
	int	signo;
	int	re_status;

	signo = WTERMSIG(status);
	if (signo == SIGINT && *flag == 0)
		ft_putstr_fd("^C\n", 2);
	else if (signo == SIGQUIT && *flag == 0)
		ft_putstr_fd("^\\QUIT: 3\n", 2);
	(*flag)++;
	re_status = 128 + status;
	return (re_status);
}
