/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_atoi.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junglee <junglee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 17:20:05 by junglee           #+#    #+#             */
/*   Updated: 2023/08/04 17:00:41 by junglee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

static int	ft_checksign(const char *str)
{
	int	i;

	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	while (str[i])
	{
		if (str[i] == '-' || str[i] == '+')
		{
			if (!(str[i + 1] >= '0' && str[i + 1] <= '9'))
				return (0);
			if (str[i] == '-')
				return (-1);
			else
				return (1);
		}
		else if (str[i] >= '0' && str[i] <= '9')
			return (1);
		else
			return (0);
		i++;
	}
	return (0);
}

static int	ft_under_over_check(unsigned long long sum, int sign)
{
	if (sum - 1 > LLONG_MAX && sign == -1)
		return (0);
	if (sum > LLONG_MAX && sign == 1)
		return (-1);
	return ((int)(sum * sign));
}

static void	under_over_error(const char *str)
{
	printf("minishell: exit: %s numeric argument required\n", str);
	exit(255);
}

unsigned char	mini_atoi(const char *str)
{
	int					i;
	int					sign;
	long long			sum;
	unsigned char		output;

	i = 0;
	sign = ft_checksign(str);
	sum = 0;
	if (sign == 0)
		return (0);
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
		{
			if (LLONG_MAX / 10 < sum || (LLONG_MAX - (str[i] - 48)) < sum)
				under_over_error(str);
			sum = sum * 10 + (str[i] - 48);
		}
		else if (i > 0 && (str[i - 1] >= '0' && str[i - 1] <= '9')
			&& !(str[i] >= '0' && str[i] <= '0'))
			break ;
		i++;
	}
	output = ft_under_over_check(sum, sign);
	return (output);
}
