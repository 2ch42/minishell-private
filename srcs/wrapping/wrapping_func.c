/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wrapping_func.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junglee <junglee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 16:00:06 by junglee           #+#    #+#             */
/*   Updated: 2023/08/08 13:59:53 by junglee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wrapping.h"
#include "builtin.h"
#include <unistd.h>
#include <stdio.h>

int	stat_s(const char *restrict path, struct stat *restrict buf)
{
	int	re;

	re = stat(path, buf);
	if (re == -1)
	{
		cd_found_err(path);
		return (-1);
	}
	return (re);
}

int	access_s(const char *path, int mode)
{
	int	re;

	re = access(path, mode);
	return (re);
}

int	chdir_s(const char *path)
{
	int	re;

	re = chdir(path);
	if (re == -1)
	{
		perror("chdir");
		exit(1);
	}
	return (re);
}

int	dup_s(int fildes)
{
	int	re;

	re = dup(fildes);
	if (re == -1)
	{
		perror("dup");
		exit(1);
	}
	return (re);
}

void	*malloc_s(size_t size)
{
	void	*re;

	re = malloc(size);
	if (!re)
	{
		write(2, "malloc crash!\n", ft_strlen("malloc crash!\n"));
		exit(1);
	}
	return (re);
}
