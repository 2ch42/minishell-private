/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_func_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junglee <junglee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 22:05:30 by junglee           #+#    #+#             */
/*   Updated: 2023/08/09 22:09:27 by junglee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

void	add_non_value(t_node *node, const char *value, \
int eq_sign_flag)
{
	char	*temp;

	if (value[0] == 0)
	{
		if (eq_sign_flag)
		{
			temp = node->value;
			node->value = ft_strdup("");
			node->equel_sign = eq_sign_flag;
			free(temp);
		}
		return ;
	}
	temp = node->value;
	node->value = ft_strdup(value);
	node->equel_sign = eq_sign_flag;
	free(temp);
}
