/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junglee <junglee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 20:45:15 by junglee           #+#    #+#             */
/*   Updated: 2023/08/08 18:34:09 by junglee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "wrapping.h"
#include <unistd.h>
#include <stdio.h>

static int	is_dir(t_hash_map *env, char *path);
static int	pwd_set(t_hash_map *env, const char *path);

int	mini_cd(t_hash_map *env, char *cd_arg[])
{
	char		*path;
	struct stat	buf;
	int			status;

	path = cd_arg[1];
	status = 0;
	if (path == 0)
	{
		path = get_value(env, "HOME");
		pwd_set(env, path);
	}
	else
	{
		status = stat_s(path, &buf);
		if (status == -1)
			return (1);
		if (S_ISDIR(buf.st_mode))
			status = is_dir(env, path);
		else
		{
			cd_not_dir_err(path);
			status = 1;
		}
	}
	return (status);
}

static int	is_dir(t_hash_map *env, char *path)
{
	int	status;

	if (access_s(path, R_OK) == 0)
		status = pwd_set(env, path);
	else
	{
		cd_permission_err(path);
		return (1);
	}
	return (status);
}

static int	pwd_set(t_hash_map *env, const char *path)
{
	char	*old_path;
	char	*cur_path;
	char	*temp;

	old_path = getcwd(0, 0);
	if (path == 0)
		return (0);
	chdir_s(path);
	cur_path = getcwd(0, 0);
	if (cur_path == 0 || old_path == 0)
		return (1);
	temp = old_path;
	add_value(env, "OLDPWD", old_path, 1);
	free(temp);
	temp = cur_path;
	add_value(env, "PWD", cur_path, 1);
	free(temp);
	return (0);
}
