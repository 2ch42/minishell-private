/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junglee <junglee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 20:49:19 by changhyl          #+#    #+#             */
/*   Updated: 2023/08/08 15:37:29 by changhyl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "token.h"
#include "wrapping.h"

int	is_ad(char c)
{
	if (('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z'))
		return (1);
	if (c >= '0' && c <= '9')
		return (1);
	if (c == '_')
		return (1);
	else
		return (0);
}

static int	get_expand_area(t_tk *tk, int idx)
{
	idx += 1;
	while (*(tk->str + idx) && is_ad(*(tk->str + idx)))
	{
		idx++;
	}
	return (idx - 1);
}

char	*make_exp_key(t_tk *tk, int idx)
{
	char	*str;
	int		i;
	int		len;

	len = get_expand_area(tk, idx) - idx;
	str = (char *)malloc_s(sizeof(char) * (len + 1));
	i = 0;
	while (i < len)
	{
		*(str + i) = *(tk->str + idx + 1 + i);
		i++;
	}
	*(str + i) = '\0';
	return (str);
}
