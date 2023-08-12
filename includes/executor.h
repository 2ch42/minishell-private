/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junglee <junglee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 16:20:18 by junglee           #+#    #+#             */
/*   Updated: 2023/08/09 21:54:36 by junglee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "builtin.h"
# include "token.h"

# define READ 0
# define WRITE 1
# define IN 0
# define OUT 1

enum e_word {
	BUILTIN,
	EXECVE
};

typedef struct s_heredoc_info
{
	int		fd;
	char	*file_name;
	int		eof;
}	t_heredoc_info;

//exit_error
void	ft_putstr_fd(const char *s, int fd);
void	ft_putendl_fd(const char *s, int fd);
void	exit_error(const char *err_str, int exit_code);
void	file_not_found_err(const char *file_path);
void	permission_err(const char *file_path);

//redirect
void	redirect_left(const char *file_path, int *fd, int *file_status);
void	redirect_right(const char *file_path, int *fd, int *file_status);
void	here_doc(const char *delimter, t_heredoc_info *here_doc_info);
void	redirect_append(const char *file_path, int *fd, int *file_status);

//std_inout_redirect
void	save_std_fd(int parent_std_fd[2]);
void	init_std_fd(int parent_std_fd[2]);

//regen_close_pipe
void	regen_pipe(int pipe_fd[2][2], int i, int pipe_num);
void	close_pipe(int pipe_fd[2][2], int i, int pipe_num);

//pipe_redirect
void	redirect_pipe_children(int pipe_fd[2][2], int i, int pipe_num);
void	set_pipe_direction(int i, int *read, int *write);

//wait_child
int		wait_child_process(pid_t *pid_arr, int pipe_num);
void	fd_close_and_word_free(int std_fd[2], char **word_arg);

//mini_excutor
void	mini_execute(t_tk_list *tk_list, t_hash_map *env, char *envp[]);

//executor_utils
void	free_arg(char *cmd_arg[]);
int		builtin_check(const char *word);
int		builtin_execute(char *word_arg[], const char *word, t_hash_map *env);
int		pipe_count(t_tk_list *tk_list);
void	add_exit_status(int status, t_hash_map *env);

//executor_utils2
int		parent_builtin_check(t_tk *token);
void	child_heredoc(t_tk_list *tk_list, t_heredoc_info *here_doc_info);

//token_to_word_arg
t_tk	*token_move_to_pipe(t_tk *token, int i);
char	**tk_redirect(t_tk *token, int std_fd[2], int *file_status);

//heredoc_utils
int		here_doc_count(t_tk_list *tk_list);
void	here_doc_delete(t_heredoc_info *here_doc_info, int here_doc_num);
void	buf_nl_clear(char *buf);
char	*get_here_doc_file_name(void);
void	heredoc_file_change(t_tk_list *tk_list, t_heredoc_info *here_doc_info);

//heredoc_utils2
void	heredoc_name_change(t_tk_list *tk_list, t_heredoc_info *here_doc_info);
void	heredoc_sigint(t_hash_map *env, t_heredoc_info *here_doc_info, \
int here_doc_num);
int		heredoc_wait(pid_t pid);

//cmdfile_path_check
char	*get_cmd_path(char *cmd, t_hash_map *env);
#endif