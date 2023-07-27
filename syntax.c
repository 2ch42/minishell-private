/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: changhyl <changhyl@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 20:45:13 by changhyl          #+#    #+#             */
/*   Updated: 2023/07/27 22:48:03 by changhyl         ###   ########.fr       */
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

t_tk	*check_op_syntax(t_tk_list *tk_list)
{
	t_tk	p;
	t_tk	q;

	if (tk_list->head == NULL)
		return (NULL);
	p = tk_list->head->next;
	q = tk_list->head;
	while (p != NULL)
	{
		if (is_op_or_m(p->str) && is_op_or_m(q->str))
			return (p);
		q = p;
		p = p->next;
	}
	return (NULL);
}

t_tk_list	*check_syntax(char *str)
{
	t_tk_list	*tk_list;
	t_tk		*tk;

	tk_list = tokenize(str);
	if (!tk_list)
		return ;
	if (tk_list->tail->single_q % 2 == 1 || tk_list->tail->double_q % 2 == 1)
	{
		write(2, "minishell: syntax error near unexpected token `newline'\n", 57);
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
	return (tk_list);
}
