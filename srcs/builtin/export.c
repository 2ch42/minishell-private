/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junglee <junglee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 17:18:25 by junglee           #+#    #+#             */
/*   Updated: 2023/08/08 18:20:19 by junglee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "utils.h"
#include <stdio.h>

static void	export_print(t_hash_map *hash_map);
static void	export_insert(t_hash_map *hash_map, char *export_arg[], \
int *status);
static void	invalid_name_err(char *export_arg[], \
const char *name, const char *value, int i);

int	mini_export(t_hash_map *hash_map, char *export_arg[])
{
	int	status;

	status = 0;
	if (export_arg[1] == 0)
		export_print(hash_map);
	else
		export_insert(hash_map, export_arg, &status);
	return (status);
}

static void	export_print(t_hash_map *hash_map)
{
	int	i;

	i = 0;
	while (i < 53)
	{
		list_print(&hash_map->linked_list[i]);
		i++;
	}
}

static void	export_insert(t_hash_map *hash_map, char *export_arg[], int *status)
{
	int		i;
	char	*name;
	char	*value;
	char	**name_and_value;

	i = 1;
	while (export_arg[i])
	{
		name_and_value = export_split(export_arg[i]);
		name = name_and_value[0];
		value = name_and_value[1];
		if (name_valid_check(name) == INVALID)
		{
			(*status) = 1;
			invalid_name_err(export_arg, name, value, i);
			free_split_str(name_and_value);
			i++;
			continue ;
		}
		add_value(hash_map, name, value, equel_sign_check(export_arg[i]));
		free_split_str(name_and_value);
		i++;
	}
}

static void	invalid_name_err(char *export_arg[], \
const char *name, const char *value, int i)
{
	ft_putstr_fd("export: \'", 2);
	ft_putstr_fd(name, 2);
	if (equel_sign_check(export_arg[i]))
		ft_putstr_fd("=", 2);
	ft_putstr_fd(value, 2);
	ft_putstr_fd("\': not a valid identifier\n", 2);
}
