/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junglee <junglee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 16:27:00 by junglee           #+#    #+#             */
/*   Updated: 2023/08/07 16:19:42 by junglee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include <unistd.h>

void	ft_putstr_fd(const char *s, int fd)
{
	int	i;

	i = 0;
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
}

void	ft_putendl_fd(const char *s, int fd)
{
	ft_putstr_fd(s, fd);
	write(fd, "\n", 1);
}

void	exit_error(const char *err_str, int exit_code)
{
	ft_putendl_fd((char *)err_str, 2);
	exit(exit_code);
}

void	file_not_found_err(const char *file_path)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(file_path, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
}

void	permission_err(const char *file_path)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(file_path, 2);
	ft_putstr_fd(": Permission denied\n", 2);
}
