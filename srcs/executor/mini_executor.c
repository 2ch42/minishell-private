/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_executor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junglee <junglee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 14:04:13 by junglee           #+#    #+#             */
/*   Updated: 2023/08/09 22:08:53 by junglee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "utils.h"
#include "wrapping.h"
#include "sig.h"
#include <unistd.h>
#include <stdio.h>

static int	pipe_execute(t_tk_list *tk_list, int pipe_num, \
t_hash_map *env, char *envp[]);
static int	child_execute(t_tk *token, t_hash_map *env, char *envp[]);
static int	parent_execute(t_tk_list *tk_list, t_hash_map *env, char *envp[]);
static int	here_doc_execute(t_tk_list *tk_list, t_heredoc_info *here_doc_info);

void	mini_execute(t_tk_list *tk_list, t_hash_map *env, char *envp[])
{
	int				pipe_num;
	int				here_doc_num;
	t_heredoc_info	*here_doc_info;
	int				exit_status;
	int				parent_std_fd[2];

	pipe_num = pipe_count(tk_list);
	here_doc_num = here_doc_count(tk_list);
	here_doc_info = (t_heredoc_info *)malloc_s(sizeof(t_heredoc_info) * \
	here_doc_num);
	if (here_doc_execute(tk_list, here_doc_info))
	{
		heredoc_sigint(env, here_doc_info, here_doc_num);
		return ;
	}
	if (pipe_num > 0)
		exit_status = pipe_execute(tk_list, pipe_num, env, envp);
	else
	{
		save_std_fd(parent_std_fd);
		exit_status = parent_execute(tk_list, env, envp);
		init_std_fd(parent_std_fd);
	}
	here_doc_delete(here_doc_info, here_doc_num);
	add_exit_status(exit_status, env);
}

static int	pipe_execute(t_tk_list *tk_list, int pipe_num, \
t_hash_map *env, char *envp[])
{
	int		pipe_fd[2][2];
	pid_t	*pid_arr;
	int		i;
	t_tk	*token;

	i = 0;
	pid_arr = (pid_t *)malloc_s(sizeof(pid_t) * (pipe_num + 1));
	token = tk_list->head;
	while (i <= pipe_num)
	{
		regen_pipe(pipe_fd, i, pipe_num);
		token = token_move_to_pipe(token, i);
		sig_handler(DEFAULT, DEFAULT);
		pid_arr[i] = fork_s();
		if (pid_arr[i] == 0)
		{
			redirect_pipe_children(pipe_fd, i, pipe_num);
			exit (child_execute(token, env, envp));
		}
		else
			close_pipe(pipe_fd, i, pipe_num);
		sig_handler(IGNORE, IGNORE);
		i++;
	}
	return (wait_child_process(pid_arr, pipe_num));
}

static int	child_execute(t_tk *token, t_hash_map *env, char *envp[])
{
	char	**word_arg;
	int		std_fd[2];
	int		status;
	int		file_status;

	status = 0;
	file_status = 0;
	word_arg = tk_redirect(token, std_fd, &file_status);
	if (file_status > 0)
	{
		close(std_fd[IN]);
		close(std_fd[OUT]);
		return (1);
	}
	if (!word_arg[0])
	{
		free(word_arg);
		return (status);
	}
	if (builtin_check(word_arg[0]) == BUILTIN)
		status = builtin_execute(word_arg, word_arg[0], env);
	else
		execve_s(get_cmd_path(word_arg[0], env), word_arg, envp);
	fd_close_and_word_free(std_fd, word_arg);
	return (status);
}

static int	parent_execute(t_tk_list *tk_list, t_hash_map *env, char *envp[])
{
	pid_t	pid;
	t_tk	*token;
	int		status;

	token = tk_list->head;
	status = 0;
	if (parent_builtin_check(token) == BUILTIN)
		return (child_execute(token, env, envp));
	else
	{
		sig_handler(DEFAULT, DEFAULT);
		pid = fork_s();
		if (pid == 0)
			exit (child_execute(token, env, envp));
		if (pid != 0)
			sig_handler(IGNORE, IGNORE);
		status = wait_child_process(&pid, 0);
	}
	return (status);
}

static int	here_doc_execute(t_tk_list *tk_list, t_heredoc_info *here_doc_info)
{
	pid_t	pid;
	int		status;

	status = 0;
	sig_handler(IGNORE, IGNORE);
	heredoc_file_change(tk_list, here_doc_info);
	pid = fork_s();
	if (pid == 0)
	{
		sig_handler(DEFAULT, IGNORE);
		child_heredoc(tk_list, here_doc_info);
		exit(0);
	}
	else
		status = heredoc_wait(pid);
	sig_handler(PROMPT, PROMPT);
	heredoc_name_change(tk_list, here_doc_info);
	return (status);
}
