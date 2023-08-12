/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junglee <junglee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 19:50:08 by changhyl          #+#    #+#             */
/*   Updated: 2023/08/06 14:18:36 by changhyl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"
#include "wrapping.h"
#include <stdlib.h>

static void	del_q_util(t_tk *tk, char *new_str, int *i, int *j)
{
	if (*(tk->str + *i) == '\'')
	{
		*i += 1;
		while (*(tk->str + *i) != '\'')
		{
			*(new_str + *j) = *(tk->str + *i);
			*i += 1;
			*j += 1;
		}
		*i += 1;
	}
	else if (*(tk->str + *i) == '\"')
	{
		*i += 1;
		while (*(tk->str + *i) != '\"')
		{
			*(new_str + *j) = *(tk->str + *i);
			*i += 1;
			*j += 1;
		}
		*i += 1;
	}
	return ;
}

void	del_q(t_tk *tk)
{
	char	*new_str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new_str = (char *)malloc(sizeof(char)
			* (tk_strlen(tk->str) - tk->double_q - tk->single_q + 1));
	*(new_str + tk_strlen(tk->str) - tk->double_q - tk->single_q) = '\0';
	while (*(tk->str + i))
	{
		if ((*(tk->str + i) == '\'') || (*(tk->str + i) == '\"'))
			del_q_util(tk, new_str, &i, &j);
		else
		{
			*(new_str + j) = *(tk->str + i);
			j++;
			i++;
		}
	}
	free(tk->str);
	tk->str = new_str;
}
