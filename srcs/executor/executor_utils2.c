/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junglee <junglee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 16:04:15 by junglee           #+#    #+#             */
/*   Updated: 2023/08/09 21:44:07 by junglee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "token.h"

int	parent_builtin_check(t_tk *token)
{
	while (token)
	{
		if (token->tktype == word)
			return (builtin_check(token->str));
		token = token->next;
	}
	return (EXECVE);
}

void	child_heredoc(t_tk_list *tk_list, t_heredoc_info *here_doc_info)
{
	t_tk	*head;
	int		i;

	head = tk_list->head;
	i = 0;
	while (head)
	{
		if (head->tktype == heredoc)
		{
			here_doc(head->next->str, &here_doc_info[i]);
			i++;
		}
		head = head->next;
	}
}
