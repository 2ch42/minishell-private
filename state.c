/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: changhyl <changhyl@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 19:43:24 by changhyl          #+#    #+#             */
/*   Updated: 2023/07/20 21:48:44 by changhyl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

int	is_outside(char c)
{
	if (c == ' ' || c == '\t' || c == '\v'
		|| c == '\f' || c == '\r')
		return (1);
	return (0);
}

int	is_quote(char c)
{
	if (c == '\"' || '\'')
		return (1);
	return (0);
}

int	is_op(char c)
{
	if (c == '|')
		return (1);
	return (0);
}

int	is_may_change(char c)
{
	if (c == '<' || c == '>')
		return (1);
	return (0);
}

t_tk_st	check_st(char c)
{
	if (is_outside(c))
		return (outside);
	else if (is_quote(c))
		return (quote);
	else if (is_op(c))
		return (op);
	else if (is_may_change(c))
		return (may_change);
	else
		return (inside);
}
