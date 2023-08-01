/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: changhyl <changhyl@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 16:53:54 by changhyl          #+#    #+#             */
/*   Updated: 2023/08/01 18:42:30 by changhyl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "token.h"

void	syn_err_nl(t_tk_list *tk_list)
{
	write(2, "minishell: syntax error near ", 30);
	write(2, "unexpected token `newline'\n", 28);
	tk_clear(tk_list);
}

void	syn_err_nnl(char *str, t_tk_list *tk_list)
{
	write(2, "minishell: syntax error near unexpected token '", 47);
	write(2, str, tk_strlen(str) + 1);
	write(2, "'\n", 3);
	tk_clear(tk_list);
}
