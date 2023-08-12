/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junglee <junglee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 18:54:45 by junglee           #+#    #+#             */
/*   Updated: 2023/08/08 23:16:44 by changhyl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include <stdio.h>
#include <unistd.h>

int	mini_pwd(void)
{
	char	*working_dir;

	working_dir = getcwd(0, 0);
	printf("%s\n", working_dir);
	free(working_dir);
	return (0);
}
