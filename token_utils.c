/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: changhyl <changhyl@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 20:53:01 by changhyl          #+#    #+#             */
/*   Updated: 2023/07/21 16:29:04 by changhyl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static size_t	ft_strlen(const	char *s)
{
	int	len;

	len = 0;
	while (*(s + len) != '\0')
	{
		len++;
	}
	return (len);
}

char	*tk_strjoin(char *s1, char s2)
{
	char	*ret_str;
	size_t	s1_len;
	size_t	i;

	s1_len = ft_strlen(s1);
	ret_str = (char *)malloc(sizeof(char) * (s1_len + 2));
	if (!ret_str)
		return (NULL);
	i = 0;
	while (i < s1_len)
	{
		*(ret_str + i) = *(s1 + i);
		i++;
	}
	*(ret_str + i) = s2;
	*(ret_str + i + 1) = '\0';
	if (s1 != NULL)
	{
		free(s1);
		s1 = NULL;
	}
	return (ret_str);
}