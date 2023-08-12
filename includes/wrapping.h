/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wrapping.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junglee <junglee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 15:56:46 by junglee           #+#    #+#             */
/*   Updated: 2023/08/08 18:55:09 by junglee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WRAPPING_H
# define WRAPPING_H

# include <stdlib.h>
# include <sys/stat.h>

int		stat_s(const char *restrict path, struct stat *restrict buf);
int		access_s(const char *path, int mode);
int		chdir_s(const char *path);
void	*malloc_s(size_t size);
int		open_s(const char *path, int oflag, ...);
void	pipe_s(int pipe_fd[2]);
void	close_s(int pipe_fd);
int		dup_s(int fildes);
void	dup2_s(int fd1, int fd2);
pid_t	fork_s(void);
int		execve_s(const char *path, char *const argv[], char *const envp[]);

#endif