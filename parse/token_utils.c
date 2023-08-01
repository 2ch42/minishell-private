/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: changhyl <changhyl@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 22:49:17 by changhyl          #+#    #+#             */
/*   Updated: 2023/08/01 19:56:26 by changhyl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "token.h"

size_t	tk_strlen(const	char *s)
{
	int	len;

	len = 0;
	while (*(s + len) != '\0')
	{
		len++;
	}
	return (len);
}

static char	*tk_cjoin(t_tk *tk, char s2)
{
	char	*ret_str;

	ret_str = (char *)malloc(sizeof(char) * 2);
	*ret_str = s2;
	*(ret_str + 1) = '\0';
	tk->new_sig = 0;
	return (ret_str);
}

char	*tk_strjoin(t_tk *tk, char s2)
{
	char	*ret_str;
	size_t	s1_len;
	size_t	i;

	if (tk->new_sig == 1)
		return (tk_cjoin(tk, s2));
	s1_len = tk_strlen(tk->str);
	ret_str = (char *)malloc(sizeof(char) * (s1_len + 2));
	if (!ret_str)
		return (NULL);
	i = 0;
	while (i < s1_len)
	{
		*(ret_str + i) = *(tk->str + i);
		i++;
	}
	*(ret_str + i) = s2;
	*(ret_str + i + 1) = '\0';
	if (tk->str != NULL)
	{
		free(tk->str);
		tk->str = NULL;
	}
	return (ret_str);
}
