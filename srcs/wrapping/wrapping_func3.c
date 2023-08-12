/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wrapping_func3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junglee <junglee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 14:34:49 by junglee           #+#    #+#             */
/*   Updated: 2023/08/06 14:36:32 by junglee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wrapping.h"
#include "executor.h"
#include <unistd.h>

int	execve_s(const char *path, char *const argv[], char *const envp[])
{
	if (execve(path, argv, envp) < 0)
		exit_error("minishell: execve error", 1);
	return (-1);
}
