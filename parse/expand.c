/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: changhyl <changhyl@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 20:49:10 by changhyl          #+#    #+#             */
/*   Updated: 2023/08/02 21:03:53 by changhyl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "token.h"
#include "builtin.h"

void	run_exp(t_tk *tk, int i)
{
	if (*(tk->str + i + 1))
}

void	check_exp(t_tk *tk, t_hash_map *hash_map)
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
						i = run_exp(tk, i);
				i++;
			}
		}
		if (*(tk->str + i) == '$')
			i = run_exp(tk, i);
		i++;
	}
}

t_tk_list	*expand(char *str, t_hash_map *hash_map)
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
