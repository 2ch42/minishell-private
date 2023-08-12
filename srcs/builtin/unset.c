/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junglee <junglee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 14:47:38 by junglee           #+#    #+#             */
/*   Updated: 2023/08/08 14:05:04 by junglee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include <stdio.h>

static void	unset_delete(t_hash_map *hasm_map, char *unset_arg[])
{
	int	i;

	i = 1;
	while (unset_arg[i])
	{
		delete_value(hasm_map, unset_arg[i]);
		i++;
	}
}

int	mini_unset(t_hash_map *hash_map, char *unset_arg[])
{
	if (unset_arg[1] == 0)
	{
		return (0);
	}
	unset_delete(hash_map, unset_arg);
	return (0);
}
