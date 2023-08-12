/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junglee <junglee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 19:22:56 by junglee           #+#    #+#             */
/*   Updated: 2023/08/06 17:43:41 by junglee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "wrapping.h"

static void	put_name(char *name, const char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i] && str[i] != '=')
	{
		name[j] = str[i];
		j++;
		i++;
	}
	name[j] = 0;
}

static void	put_value(char *value, const char *str)
{
	int	i;
	int	j;

	if (!(*str) || !str)
	{
		value[0] = 0;
		return ;
	}
	i = 1;
	j = 0;
	while (str[i])
	{
		value[j] = str[i];
		j++;
		i++;
	}
	value[j] = 0;
}

static int	name_count(const char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	return (i);
}

static int	value_count(const char *str)
{
	int	i;

	if (!(*str) || !str)
		return (0);
	i = 1;
	while (str[i])
		i++;
	return (i - 1);
}

char	**export_split(const char *str)
{
	int		name_len;
	int		value_len;
	char	**name_value;

	name_value = (char **)malloc_s(sizeof(char *) * 3);
	name_len = name_count(str);
	name_value[0] = (char *)malloc_s(sizeof(char) * (name_len + 1));
	put_name(name_value[0], str);
	value_len = value_count(str + name_len);
	name_value[1] = (char *)malloc_s(sizeof(char) * (value_len + 1));
	put_value(name_value[1], str + name_len);
	name_value[2] = 0;
	return (name_value);
}
