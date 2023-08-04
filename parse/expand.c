/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: changhyl <changhyl@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 20:49:10 by changhyl          #+#    #+#             */
/*   Updated: 2023/08/04 15:54:44 by changhyl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "token.h"
#include "builtin.h"

static char	*get_new_str(t_tk *tk, char *new_str, int i, int end_idx)
{
	int	j;

	j = 0;
	while (*(tk->str + end_idx + 1 + j))
	{
		*(new_str + i + j) = *(tk->str + end_idx + 1 + j);
		j++;
	}
	*(new_str + i + j) = '\0';
	free(tk->str);
	tk->str = NULL;
	return (new_str);
}

static int	run_exp(t_tk *tk, int start_idx, int end_idx, char *value)
{
	int		i;
	int		j;
	int		new_str_len;
	int		value_len;
	char	*new_str;

	i = 0;
	value_len = ft_strlen(value);
	new_str_len = ft_strlen(tk->str) - (end_idx - start_idx + 1) + value_len;
	new_str = (char *)malloc_s(sizeof(char) * (new_str_len + 1));
	while (i < start_idx)
	{
		*(new_str + i) = *(tk->str + i);
		i++;
	}
	j = 0;
	while (j < value_len)
	{
		*(new_str + i) = *(value + j);
		i++;
		j++;
	}
	tk->str = get_new_str(tk, new_str, i, end_idx);
	return (value_len);
}

static int	value_exp(t_tk *tk, int idx, t_hash_map *hash_map)
{
	char	*key;
	char	*value;
	int		value_len;

	if (*(tk->str + idx + 1) == '\0' || is_outside(*(tk->str + idx + 1)))
		return (idx);
	if (*(tk->str + idx + 1) == '\?')
	{
		value = get_value(hash_map, "?");
		value_len = run_exp(tk, idx, idx + 1, value);
	}
	else
	{
		key = make_exp_key(tk, idx);
		value = get_value(hash_map, key);
		value_len = run_exp(tk, idx, idx + ft_strlen(key), value);
		free(key);
		key = NULL;
	}
	return (idx + value_len - 1);
}

static void	check_exp(t_tk *tk, t_hash_map *hash_map)
{
	int	i;

	i = 0;
	while (*(tk->str + i))
	{
		if (*(tk->str + i) == '\'')
		{
			i++;
			while (*(tk->str + i) != '\'')
				i++;
		}
		if (*(tk->str + i) == '\"')
		{
			i++;
			while (*(tk->str + i) != '\"')
			{
				if (*(tk->str + i) == '$')
					i = value_exp(tk, i, hash_map);
				i++;
			}
		}
		if (*(tk->str + i) == '$')
			i = value_exp(tk, i, hash_map);
		i++;
	}
}

t_tk_list	*mini_expand(char *str, t_hash_map *hash_map)
{
	t_tk_list	*tk_list;
	t_tk		*tk;

	tk_list = check_syntax(str);
	if (!tk_list)
		return (NULL);
	tk = tk_list->head;
	if (tk == NULL)
		return (tk_list);
	while (tk != NULL)
	{
		if (tk->tktype == word && tk->str != NULL)
			check_exp(tk, hash_map);
		tk = tk->next;
	}
	return (tk_list);
}
