/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: changhyl <changhyl@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 19:27:30 by changhyl          #+#    #+#             */
/*   Updated: 2023/07/21 16:11:35 by changhyl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "token.h"

t_tk_list	*init_tk_list(void)
{
	t_tk_list	*new_tk_list;

	new_tk_list = (t_tk_list *)malloc(sizeof(t_tk_list));
	if (!new_tk_list)
		return (NULL);
	new_tk_list->head = NULL;
	new_tk_list->tail = NULL;
	new_tk_list->errno = 0;
}

t_tk	*init_tk(void)
{
	t_tk	new_tk;

	new_tk = (t_tk)malloc(sizeof(t_tk));
	if (!new_tk)
		return (NULL);
	new_tk->next = NULL;
	new_tk->errno = 0;
	return (new_tk);
}
