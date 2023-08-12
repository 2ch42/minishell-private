/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junglee <junglee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 15:55:03 by junglee           #+#    #+#             */
/*   Updated: 2023/08/08 22:56:00 by junglee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "utils.h"
#include <stdio.h>

static int	num_check(const char *arg);
static void	exit_num_arg_err(const char *arg);
static void	exit_finish(int status);

int	mini_exit(char *exit_arg[])
{
	unsigned char	status;
	int				i;

	status = 0;
	i = 1;
	if (exit_arg[1] == 0)
		exit_finish(status);
	if (num_check(exit_arg[i]) == VALID)
	{
		if (exit_arg[i + 1] != 0)
		{
			ft_putstr_fd("exit\n", 1);
			ft_putstr_fd("minishell: exit: too many arguments\n", 2);
			return (1);
		}
		status = mini_atoi(exit_arg[i]);
	}
	else
	{
		ft_putstr_fd("exit\n", 1);
		exit_num_arg_err(exit_arg[i]);
		exit(255);
	}
	return (status);
}

static void	exit_finish(int status)
{
	ft_putstr_fd("exit\n", 1);
	exit(status);
}

static void	exit_num_arg_err(const char *arg)
{
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
}

static int	num_check(const char *arg)
{
	int	i;

	i = 0;
	while ((arg[i] >= 9 && arg[i] <= 13) || arg[i] == 32)
		i++;
	if (arg[i] == '-' || arg[i] == '+')
		i++;
	while (arg[i])
	{
		if (!(arg[i] >= '0' && arg[i] <= '9'))
			return (INVALID);
		i++;
	}
	return (VALID);
}
