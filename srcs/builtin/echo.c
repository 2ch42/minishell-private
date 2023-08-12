/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junglee <junglee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 17:58:13 by junglee           #+#    #+#             */
/*   Updated: 2023/08/04 21:34:53 by junglee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include <stdio.h>

static int	n_flag_check(const char *arg)
{
	int		n_flag;
	int		i;
	char	sep;

	n_flag = 0;
	i = 0;
	if (arg[i] == '-')
	{
		i++;
		sep = arg[i];
		while (arg[i] && arg[i] == sep)
			i++;
		if (arg[i] == 0)
			n_flag = 1;
	}
	return (n_flag);
}

static void	echo_print(char *echo_arg[], int i)
{
	while (echo_arg[i])
	{
		printf("%s", echo_arg[i]);
		if (echo_arg[i + 1] != 0)
			printf(" ");
		i++;
	}
}

int	mini_echo(char *echo_arg[])
{
	int	i;
	int	prev_n_flag;
	int	n_flag;

	i = 1;
	prev_n_flag = 0;
	while (echo_arg[i])
	{
		n_flag = n_flag_check(echo_arg[i]);
		if (n_flag)
		{
			i++;
			prev_n_flag = n_flag;
			continue ;
		}
		break ;
	}
	echo_print(echo_arg, i);
	if (prev_n_flag == 0)
		printf("\n");
	return (0);
}
