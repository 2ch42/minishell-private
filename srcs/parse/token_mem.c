/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_mem.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junglee <junglee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 20:05:35 by changhyl          #+#    #+#             */
/*   Updated: 2023/08/06 18:41:24 by junglee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "token.h"

void	tk_clear(t_tk_list *tk_list)
{
	t_tk	*p;
	t_tk	*q;

	if (tk_list->head != NULL)
	{
		p = tk_list->head->next;
		q = tk_list->head;
		while (p != NULL)
		{
			free(q->str);
			q->str = NULL;
			free(q);
			q = NULL;
			q = p;
			p = p->next;
		}
		free(q->str);
		q->str = NULL;
		free(q);
		q = NULL;
	}
	free(tk_list);
	tk_list = NULL;
}
