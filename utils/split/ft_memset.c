/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junglee <junglee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 20:25:06 by junglee           #+#    #+#             */
/*   Updated: 2023/08/08 18:53:11 by junglee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t			count;
	unsigned char	*ucb;

	count = 0;
	ucb = (unsigned char *)b;
	while (count < len)
	{
		*ucb = (unsigned char)c;
		count++;
		ucb++;
	}
	return (b);
}
