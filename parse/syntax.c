/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: changhyl <changhyl@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 20:45:13 by changhyl          #+#    #+#             */
/*   Updated: 2023/07/28 21:08:26 by changhyl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "token.h"

static int	is_op_or_m(char c)
{
	if (c == '|')
		return (1);
	if (c == '>')
		return (1);
	if (c == '<')
		return (1);
	return (0);
}

static t_tk	*check_op_syntax(t_tk_list *tk_list)
{
	t_tk	*p;
	t_tk	*q;

	if (tk_list->head == NULL)
		return (NULL);
	p = tk_list->head->next;
	q = tk_list->head;
	while (p != NULL)
	{
		if (is_op_or_m(*(p->str)) && is_op_or_m(*(q->str)))
			return (p);
		q = p;
		p = p->next;
	}
	return (NULL);
}

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

t_tk_list	*check_syntax(char *str)
{
	t_tk_list	*tk_list;
	t_tk		*tk;

	tk_list = tokenize(str);
	if (!tk_list)
		return (NULL);
	if (tk_list->tail->single_q % 2 == 1 || tk_list->tail->double_q % 2 == 1)
	{
		write(2, "minishell: syntax error near ", 30);
		write(2, "unexpected token `newline'\n", 28);
		tk_clear(tk_list);
		return (NULL);
	}
	tk = check_op_syntax(tk_list);
	if (tk != NULL)
	{
		write(2, "minishell: syntax error near unexpected token '", 47);
		write(2, tk->str, tk_strlen(tk->str) + 1);
		write(2, "'\n", 3);
		tk_clear(tk_list);
		return (NULL);
	}
	fill_tktype(tk_list);
	return (tk_list);
}
