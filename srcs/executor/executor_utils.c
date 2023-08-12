/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junglee <junglee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 15:04:28 by junglee           #+#    #+#             */
/*   Updated: 2023/08/08 22:44:13 by junglee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "utils.h"
#include "builtin.h"

void	free_arg(char *cmd_arg[])
{
	int	i;

	i = 0;
	while (cmd_arg[i])
	{
		free(cmd_arg[i]);
		i++;
	}
	free(cmd_arg);
}

int	builtin_check(const char *word)
{
	if (ft_strcmp(word, "echo") == 0 || \
		ft_strcmp(word, "cd") == 0 || \
		ft_strcmp(word, "pwd") == 0 || \
		ft_strcmp(word, "export") == 0 || \
		ft_strcmp(word, "unset") == 0 || \
		ft_strcmp(word, "env") == 0 || \
		ft_strcmp(word, "exit") == 0)
	{
		return (BUILTIN);
	}
	else
		return (EXECVE);
}

int	builtin_execute(char *word_arg[], const char *word, t_hash_map *env)
{
	if (ft_strcmp(word, "echo") == 0)
		return (mini_echo(word_arg));
	else if (ft_strcmp(word, "cd") == 0)
		return (mini_cd(env, word_arg));
	else if (ft_strcmp(word, "pwd") == 0)
		return (mini_pwd());
	else if (ft_strcmp(word, "export") == 0)
		return (mini_export(env, word_arg));
	else if (ft_strcmp(word, "unset") == 0)
		return (mini_unset(env, word_arg));
	else if (ft_strcmp(word, "env") == 0)
		return (mini_env(env));
	else if (ft_strcmp(word, "exit") == 0)
		return (mini_exit(word_arg));
	else
	{
		exit_error("builtin_execute error!\n", 1);
		return (0);
	}
}

int	pipe_count(t_tk_list *tk_list)
{
	t_tk	*head;
	int		pipe_num;

	pipe_num = 0;
	head = tk_list->head;
	while (head)
	{
		if (head->tktype == pipeline)
			pipe_num++;
		head = head->next;
	}
	return (pipe_num);
}

void	add_exit_status(int status, t_hash_map *env)
{
	char	*str;

	str = ft_itoa(status);
	add_value(env, "?", str, 1);
	free(str);
}
