/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junglee <junglee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 15:36:15 by junglee           #+#    #+#             */
/*   Updated: 2023/07/24 16:41:43 by junglee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

void	init_list(t_list *list)
{
	list->head = (t_node *)malloc(sizeof(t_node));
	list->head->next = 0;
	list->head->key = 0;
	list->head->value = 0;
	list->size = 0;
}

t_node	*key_check(t_list *list, const char *key)
{
	t_node	*temp;

	temp = list->head->next;
	while (temp)
	{
		if (ft_strcmp(temp->key, key) == 0)
			return (temp);
		temp = temp->next;
	}
	return (temp);
}

void	add_node(t_list *list, const char *key, const char *value, \
int eq_sign_flag)
{
	t_node	*temp;
	t_node	*node;

	temp = new_node(key, value, eq_sign_flag);
	if (list->size == 0)
	{
		list->head->next = temp;
		temp->next = 0;
		(list->size)++;
		return ;
	}
	else
	{
		node = list->head;
		while (node->next && ft_strcmp(temp->key, node->next->key) > 0)
			node = node->next;
		temp->next = node->next;
		node->next = temp;
		(list->size)++;
	}
}

void	delete_node(t_list *list, const char *key)
{
	t_node	*temp;
	t_node	*node;

	if (list->size == 0)
		return ;
	else
	{
		node = list->head;
		while (node->next)
		{
			if (ft_strcmp(node->next->key, key) == 0)
			{
				temp = node->next;
				node->next = temp->next;
				free(temp->key);
				free(temp->value);
				free(temp);
				(list->size)--;
				return ;
			}
			node = node->next;
		}
	}
}
