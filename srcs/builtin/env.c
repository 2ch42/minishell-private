/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junglee <junglee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 18:50:56 by junglee           #+#    #+#             */
/*   Updated: 2023/08/08 18:23:11 by junglee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include <stdio.h>

static void	env_print(t_list *list);

int	mini_env(t_hash_map *hash_map)
{
	int	i;

	i = 0;
	while (i < 53)
	{
		env_print(&hash_map->linked_list[i]);
		i++;
	}
	return (0);
}

static void	env_print(t_list *list)
{
	t_node	*temp;

	temp = list->head->next;
	while (temp)
	{
		if (temp->equel_sign)
			printf("%s=\"%s\"\n", temp->key, temp->value);
		temp = temp->next;
	}
}
