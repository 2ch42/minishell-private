/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: changhyl <changhyl@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 20:49:10 by changhyl          #+#    #+#             */
/*   Updated: 2023/08/02 21:44:30 by changhyl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "token.h"
#include "builtin.h"

static int	run_exp_exit(t_tk *tk, int i, t_hash_map *hash_map)
{
	char	*value;

	value = get_value(hash_map, "?");
	
}

static int run_exp_oth(t_tk *tk, int i, t_hash_map *hash_map)
{

}

static int	run_exp(t_tk *tk, int i, t_hash_map *hash_map)
{
	if (*(tk->str + i + 1) == '?')
		return (run_exp_exit(tk, i, hash_map));
	return (run_exp_oth(tk, i, hash_map));
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
						i = run_exp(tk, i, hash_map);
				i++;
			}
		}
		if (*(tk->str + i) == '$')
			i = run_exp(tk, i, hash_map);
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
