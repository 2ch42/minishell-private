/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: changhyl <changhyl@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 20:45:13 by changhyl          #+#    #+#             */
/*   Updated: 2023/08/07 14:19:52 by changhyl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "token.h"

void	fill_tktype(t_tk_list *tk_list)
{
	t_tk	*tk;

	if (!tk_list)
		return ;
	if (tk_list->head == NULL)
		return ;
	tk = tk_list->head;
	while (tk != NULL)
	{
		if (tk->redirect_l == 1)
			tk->tktype = redirect_l;
		else if (tk->redirect_r == 1)
			tk->tktype = redirect_r;
		else if (tk->redirect_l == 2)
			tk->tktype = heredoc;
		else if (tk->redirect_r == 2)
			tk->tktype = append;
		else if (tk->pipeline)
			tk->tktype = pipeline;
		else
			tk->tktype = word;
		tk = tk->next;
	}
	return ;
}

static int	check_op_syntax(t_tk_list *tk_list, t_hash_map *hash_map)
{
	t_tk	*p;
	t_tk	*q;

	p = tk_list->head->next;
	q = tk_list->head;
	while (p != NULL)
	{
		if ((q->tktype >= redirect_l && q->tktype <= append && p->tktype
				!= word) || (p->tktype == pipeline && q->tktype == pipeline))
		{
			syn_err_nnl(p->str, tk_list, hash_map);
			return (1);
		}
		q = p;
		p = p->next;
	}
	if (q->tktype != word)
	{
		syn_err_nl(tk_list, hash_map);
		return (1);
	}
	return (0);
}

t_tk_list	*check_syntax(char *str, t_hash_map *hash_map)
{
	t_tk_list	*tk_list;

	tk_list = tokenize(str);
	if (!tk_list)
		return (NULL);
	if (tk_list->head == NULL)
		return (tk_list);
	fill_tktype(tk_list);
	if (tk_list->head->tktype == pipeline)
	{
		syn_err_nnl(tk_list->head->str, tk_list, hash_map);
		return (NULL);
	}
	if (check_op_syntax(tk_list, hash_map) == 1)
		return (NULL);
	if (tk_list->tail->single_q % 2 == 1 || tk_list->tail->double_q % 2 == 1)
	{
		syn_err_nl(tk_list, hash_map);
		return (NULL);
	}
	return (tk_list);
}
