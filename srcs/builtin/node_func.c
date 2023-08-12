/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junglee <junglee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 16:34:56 by junglee           #+#    #+#             */
/*   Updated: 2023/08/04 16:53:56 by junglee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "utils.h"
#include "wrapping.h"

t_node	*new_node(const char *key, const char *value, int eq_sign_flag)
{
	t_node	*temp;

	temp = (t_node *)malloc_s(sizeof(t_node));
	temp->key = ft_strdup(key);
	temp->value = ft_strdup(value);
	temp->equel_sign = eq_sign_flag;
	return (temp);
}
