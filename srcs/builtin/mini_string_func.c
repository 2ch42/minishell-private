/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_string_func.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junglee <junglee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 18:01:50 by junglee           #+#    #+#             */
/*   Updated: 2023/08/06 16:08:09 by junglee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "utils.h"
#include "wrapping.h"
#include <stdio.h>

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	if (!s)
		return (0);
	while (s[len])
		len++;
	return (len);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	int		i;

	i = 0;
	if (!s1 || !s2)
	{
		perror("strcmp: ");
		exit(1);
	}
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

char	*ft_strdup(const char *s1)
{
	int		i;
	char	*dupstr;

	if (!s1)
		return (0);
	i = 0;
	dupstr = (char *)malloc_s(sizeof(char) * (ft_strlen(s1) + 1));
	while (s1[i])
	{
		dupstr[i] = s1[i];
		i++;
	}
	dupstr[i] = '\0';
	return (dupstr);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	char	*joinstr;

	i = 0;
	j = 0;
	joinstr = (char *)malloc(sizeof(char)
			* (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!joinstr)
		return (0);
	while (s1[j])
		joinstr[i++] = s1[j++];
	j = 0;
	while (s2[j])
		joinstr[i++] = s2[j++];
	joinstr[i] = '\0';
	return (joinstr);
}
