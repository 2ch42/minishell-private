/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_mem.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: changhyl <changhyl@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 20:05:35 by changhyl          #+#    #+#             */
/*   Updated: 2023/07/28 01:02:29 by changhyl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "token.h"

void	tk_clear(t_tk_list *tk_list)
{
	t_tk	*p;
	t_tk	*q;

	if (tk_list->head == NULL)
		free(tk_list);
	else
	{
		p = tk_list->head->next;
		q = tk_list->head;
		while (p != NULL)
		{
			free(q);
			q = NULL;
			q = p;
			p = p->next;
		}
		free(q);
		q = NULL;
		free(tk_list);
		tk_list = NULL;
	}
	return ;
}
