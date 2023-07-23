/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: changhyl <changhyl@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 20:45:13 by changhyl          #+#    #+#             */
/*   Updated: 2023/07/23 21:37:51 by ch               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syntax.h"

void	check_syntax(char *str)
{
	t_tk_list	*tk_list;
	
	t_tk		tk;
	tk_list = tokenize(str);
	if (!tk_list)
		return ;

}
