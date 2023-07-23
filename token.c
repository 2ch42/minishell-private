/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: changhyl <changhyl@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 20:41:29 by changhyl          #+#    #+#             */
/*   Updated: 2023/07/23 21:09:25 by ch               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "token.h"

t_tk	*add_token(t_tk_list	*tk_list)
{
	t_tk	*new_tk;

	if (!tk_list)
		tk_list = init_tk_list;
	new_tk = init_tk();
	if (!tk_list || !new_tk)
	{
		write(2, "MALLOC FAILED!!\n", 17);
		exit(1);
	}
	if (tk_list->head == NULL)
	{
		tk_list->head = tk;
		tk_list->tail = tk;
		return ;
	}
	tk_list->tail->next = tk;
	tk_list->tail = tk;
	return (tk_list->tail);
}

void	fill_token(t_tk *tk, t_state cur_st, char c)
{
	if (c == '>' && cur_st == may_change)
		tk->redirect_r++;
	else if (c == '<' && cur_st == may_change)
		tk->redirect_l++;
	else if (c == '|' && cur_st == operator)
		tk->pipeline++;
	else if (c == '\'' && cur_st == quote)
		tk->single_q++;
	else if (c == '\"' && cur_st == quote)
		tk->double_q++;
	return ;
}

int	check_new_tk(t_state prev_st, t_state cur_st)
{
	if (prev_st == outside && cur_st != outside)
		return (1);
	if (cur_st == operator)
		return (1);
	if (cur_st != outside && prev_st == operator)
		return (1);
	if (prev_st == may_change && cur_st != outside
		&& cur_st != may_change)
		return (1);
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
		if (check_new_tk(prev_st, cur_st))
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
