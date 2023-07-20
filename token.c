/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: changhyl <changhyl@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 20:41:29 by changhyl          #+#    #+#             */
/*   Updated: 2023/07/20 21:53:22 by changhyl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "token.h"

void	add_token(t_tk_list	*tk_list)
{
	t_tk	*new_tk;

	if (!tk_list)
		tk_list = init_tk_list;
	new_tk = init_tk();
	if (!tk_list || !new_tk)
		return ;
	if (tk_list->head == NULL)
	{
		tk_list->head = tk;
		tk_list->tail = tk;
		return ;
	}
	tk_list->tail->next = tk;
	tk_list->tail = tk;
}

void	fill_token(char *str, t_tk_list *tk_list)
{
	int		i;
	t_tk	*tk;

	if (tk_list == NULL || tk_list->head == NULL)
		return ;
	i = 0;
	tk = t_tk_list->head;
	while (*(str + i))
	{
		
	}
}

t_tk_list	tokenize(char *str)
{
	int			i;
	t_tk_st		prev_st;
	t_tk_st		cur_st;
	t_tk_list	tk_list;

	i = 0;
	prev_st = outside; 
	while (*(str + i))
	{
		cur_st = check_st(*(str + i));
		if (prev_st == outside && cur_st != outside)
			add_token(&tk_list);
		prev_st = cur_st;
		i++;
	}
	fill_token(str, &tk_list);
	return (tk_list);
}
