/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: changhyl <changhyl@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 20:41:29 by changhyl          #+#    #+#             */
/*   Updated: 2023/07/27 23:19:32 by changhyl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "token.h"

static t_tk	*add_token(t_tk_list	*tk_list)
{
	t_tk	*new_tk;

	if (!tk_list)
		tk_list = init_tk_list();
	new_tk = init_tk();
	if (!tk_list || !new_tk)
	{
		write(2, "malloc crash!\n", 15);
		exit(1);
	}
	if (tk_list->head == NULL)
	{
		tk_list->head = new_tk;
		tk_list->tail = new_tk;
		return (new_tk);
	}
	tk_list->tail->next = new_tk;
	tk_list->tail = new_tk;
	return (new_tk);
}

static void	fill_token(t_tk *tk, t_state cur_st, char c)
{
	if (c == '>' && cur_st == may_change)
		tk->redirect_r++;
	else if (c == '<' && cur_st == may_change)
		tk->redirect_l++;
	else if (c == '|' && cur_st == op)
		tk->pipeline++;
	else if (c == '\'' && cur_st == quote)
		tk->single_q++;
	else if (c == '\"' && cur_st == quote)
		tk->double_q++;
	return ;
}

static int	check_new_tk(t_state prev_st, t_state cur_st, t_tk *tk, char c)
{
	if (prev_st == outside && cur_st != outside)
		return (1);
	if (cur_st == op)
		return (1);
	if (cur_st != outside && prev_st == op)
		return (1);
	if (prev_st == may_change && cur_st != outside
		&& cur_st != may_change)
		return (1);
	if (tk != NULL)
	{
		if (tk->redirect_l > 0 && c == '>')
			return (1);
		if (tk->redirect_r > 0 && c == '<')
			return (1);
		if (tk->redirect_l == 2 || tk->redirect_r == 2)
			return (1);
	}
	return (0);
}

t_tk_list	*tokenize(char *str)
{
	int			i;
	t_state		prev_st;
	t_state		cur_st;
	t_tk_list	*tk_list;
	t_tk		*tk;

	i = 0;
	prev_st = outside;
	tk_list = NULL;
	tk = NULL;
	while (*(str + i))
	{
		cur_st = check_st(tk, *(str + i));
		if (check_new_tk(prev_st, cur_st, tk, *(str + i)))
			tk = add_token(tk_list);
		if (cur_st != outside)
		{
			tk->str = tk_strjoin(tk->str, *(str + i));
			fill_token(tk, cur_st, *(str + i));
		}
		prev_st = cur_st;
		i++;
	}
	return (tk_list);
}
