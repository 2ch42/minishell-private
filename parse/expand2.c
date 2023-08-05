/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junglee <junglee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 19:50:08 by changhyl          #+#    #+#             */
/*   Updated: 2023/08/04 20:53:05 by junglee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"
#include "wrapping.h"


static char	*end_exp(t_tk *tk, int start_idx, int *end_idx)
{
	char	*new_str;
	int		new_str_len;
	int		i;

	new_str_len = *end_idx - start_idx - 1;
	new_str = (char *)malloc_s(sizeof(char) * (new_str_len + 1));
	i = 0;
	while (i < new_str_len)
	{
		*(new_str + i) = *(tk->str + start_idx + 1 + i);
		i++;
	}
	*(new_str + i) = '\0';
	free(tk->str);
	tk->str = NULL;
	*end_idx -= 2;
	return (new_str);
}

void	del_q(t_tk *tk)
{
	int	i;
	int	start_idx;

	i = 0;
	while (*(tk->str + i))
	{
		if (*(tk->str + i) == '\'')
		{
			start_idx = i;
			i++;
			while (*(tk->str + i) != '\'')
				i++;
			tk->str = end_exp(tk, start_idx, &i);
		}
		else if (*(tk->str + i) == '\"')
		{
			start_idx = i;
			i++;
			while (*(tk->str + i) != '\"')
				i++;
			tk->str = end_exp(tk, start_idx, &i);
		}
		i++;
	}
}
