/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junglee <junglee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 15:21:37 by junglee           #+#    #+#             */
/*   Updated: 2023/08/09 22:09:43 by junglee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static int	indexing_order(const char *key)
{
	if (key[0] >= 'a' && key[0] <= 'z')
		return (key[0] - 'a');
	else if (key[0] >= 'A' && key[0] <= 'Z')
		return (key[0] - 39);
	else if (key[0] == '_')
		return (52);
	else
		return (53);
}

void	add_value(t_hash_map *hash_map, const char *key, const char *value, \
int eq_sign_flag)
{
	t_list	*list;
	t_node	*node;

	list = &(hash_map->linked_list[indexing_order(key)]);
	node = key_check(list, key);
	if (node != 0)
		add_non_value(node, value, eq_sign_flag);
	else
		add_node(list, key, value, eq_sign_flag);
}

void	delete_value(t_hash_map *hash_map, const char *key)
{
	t_list	*list;

	list = &(hash_map->linked_list[indexing_order(key)]);
	delete_node(list, key);
}

char	*get_value(t_hash_map *hash_map, const char *key)
{
	t_list	*list;
	t_node	*node;
	char	*value;

	list = &(hash_map->linked_list[indexing_order(key)]);
	node = list->head->next;
	value = 0;
	while (node)
	{
		if (ft_strcmp(node->key, key) == 0)
			value = node->value;
		node = node->next;
	}
	return (value);
}

void	hash_map_init(t_hash_map *hash_map, char *envp[])
{
	int			i;

	i = 0;
	while (i < 54)
	{
		init_list(&hash_map->linked_list[i]);
		i++;
	}
	mini_export(hash_map, envp);
	add_value(hash_map, "?", "0", 1);
}
