/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junglee <junglee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 19:41:40 by junglee           #+#    #+#             */
/*   Updated: 2023/08/08 18:54:02 by junglee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include <stdio.h>

int	equel_sign_check(const char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (arg[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

int	name_valid_check(const char *name)
{
	if (name[0] >= 'a' && name[0] <= 'z')
		return (VALID);
	else if (name[0] >= 'A' && name[0] <= 'Z')
		return (VALID);
	else if (name[0] == '_')
		return (VALID);
	else
		return (INVALID);
}

void	list_print(t_list *list)
{
	t_node	*temp;

	temp = list->head->next;
	while (temp)
	{
		if (temp->equel_sign)
			printf("%s=\"%s\"\n", temp->key, temp->value);
		else
			printf("%s\n", temp->key);
		temp = temp->next;
	}
}
