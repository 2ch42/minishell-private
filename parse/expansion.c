/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: changhyl <changhyl@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 20:39:21 by changhyl          #+#    #+#             */
/*   Updated: 2023/07/31 21:48:22 by ch               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "builtin.h"

t_tk_list	*(t_tk_list *tk_list, t_hash_map *hash_map)
{
	t_tk	*tk;

	if (!tk_list)
		return (NULL);
	tk = tk_list->head;
	if (!tk)
		return (tk_list);
	
}
