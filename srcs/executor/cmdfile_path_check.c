/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdfile_path_check.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junglee <junglee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 14:58:01 by junglee           #+#    #+#             */
/*   Updated: 2023/08/08 18:43:04 by junglee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "utils.h"
#include "wrapping.h"
#include <unistd.h>

static void	cmd_not_found_err(const char *cmd);
static char	*pipex_strjoin(const char *s1, const char *s2);
static void	path_disapper(const char *cmd);

char	*get_cmd_path(char *cmd, t_hash_map *env)
{
	char	*path_in_envp;
	char	**split_path;
	int		i;

	if (!access_s(cmd, F_OK))
		return (cmd);
	path_in_envp = get_value(env, "PATH");
	split_path = ft_split(path_in_envp, ':');
	if (!split_path)
		path_disapper(cmd);
	i = 0;
	while (split_path[i])
	{
		if (!(*cmd))
		{
			i++;
			continue ;
		}
		path_in_envp = pipex_strjoin(pipex_strjoin(split_path[i], "/"), cmd);
		if (!access_s(path_in_envp, F_OK))
			return (path_in_envp);
		i++;
	}
	cmd_not_found_err(cmd);
	return (0);
}

static void	cmd_not_found_err(const char *cmd)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putendl_fd(" :command not found", 2);
	exit(127);
}

static char	*pipex_strjoin(const char *s1, const char *s2)
{
	int		i;
	int		j;
	char	*joinstr;
	char	*temp;

	i = 0;
	j = 0;
	temp = (char *)s1;
	joinstr = (char *)malloc_s(sizeof(char) * \
	(ft_strlen(s1) + ft_strlen(s2) + 1));
	while (s1 && s1[j])
		joinstr[i++] = s1[j++];
	j = 0;
	while (s2 && s2[j])
		joinstr[i++] = s2[j++];
	joinstr[i] = '\0';
	free(temp);
	return (joinstr);
}

static void	path_disapper(const char *cmd)
{
	file_not_found_err(cmd);
	exit(127);
}
