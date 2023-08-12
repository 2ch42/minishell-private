/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junglee <junglee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 20:22:14 by junglee           #+#    #+#             */
/*   Updated: 2023/08/08 18:53:16 by junglee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "wrapping.h"

void	*ft_calloc(size_t count, size_t size)
{
	unsigned char	*alptr;

	alptr = (unsigned char *)malloc_s(size * count);
	if (alptr == 0)
		return (0);
	ft_bzero(alptr, size * count);
	return (alptr);
}
