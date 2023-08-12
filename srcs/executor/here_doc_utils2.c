/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junglee <junglee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 20:30:51 by junglee           #+#    #+#             */
/*   Updated: 2023/08/09 21:54:26 by junglee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include <stdio.h>

void	heredoc_name_change(t_tk_list *tk_list, t_heredoc_info *here_doc_info)
{
	t_tk	*head;
	char	*temp;
	int		i;

	head = tk_list->head;
	i = 0;
	while (head)
	{
		if (head->tktype == heredoc)
		{
			temp = head->next->str;
			head->next->str = here_doc_info[i].file_name;
			free(temp);
			i++;
		}
		head = head->next;
	}
}

void	heredoc_sigint(t_hash_map *env, t_heredoc_info *here_doc_info, \
int here_doc_num)
{
	here_doc_delete(here_doc_info, here_doc_num);
	add_exit_status(1, env);
	printf("\n");
}

int	heredoc_wait(pid_t pid)
{
	int	status;
	int	signo;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		signo = WTERMSIG(status);
		if (signo == SIGINT)
			status = 1;
	}
	return (status);
}
