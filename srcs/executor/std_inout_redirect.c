/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   std_inout_redirect.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junglee <junglee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 20:34:25 by junglee           #+#    #+#             */
/*   Updated: 2023/08/05 20:43:55 by junglee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unistd.h"
#include "executor.h"
#include "wrapping.h"

void	save_std_fd(int parent_std_fd[2])
{
	parent_std_fd[0] = dup_s(STDIN_FILENO);
	parent_std_fd[1] = dup_s(STDOUT_FILENO);
}

void	init_std_fd(int parent_std_fd[2])
{
	dup2_s(parent_std_fd[IN], STDIN_FILENO);
	dup2_s(parent_std_fd[OUT], STDOUT_FILENO);
	close(parent_std_fd[IN]);
	close(parent_std_fd[OUT]);
}
