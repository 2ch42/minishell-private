/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: changhyl <changhyl@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 19:43:24 by changhyl          #+#    #+#             */
/*   Updated: 2023/07/28 21:46:36 by changhyl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

static int	is_outside(char c)
{
	if (c == ' ' || c == '\t' || c == '\v'
		|| c == '\f' || c == '\r')
		return (1);
	return (0);
}

static int	is_quote(char c)
{
	if (c == '\"' || c == '\'')
		return (1);
	return (0);
}

static int	is_op(char c)
{
	if (c == '|')
		return (1);
	return (0);
}

static int	is_may_change(char c)
{
	if (c == '<' || c == '>')
		return (1);
	return (0);
}

t_state	check_st(t_tk *tk, char *str, int i)
{
	if (i > 0)
		if (!is_outside(*(str + i)) && *(str + i - 1) == '\\')
			return (inside);
	if (tk != NULL)
	{
		if (tk->single_q % 2 == 1 && *(str + i) != '\'')
			return (inside);
		if (tk->double_q % 2 == 1 && *(str + i) != '\"')
			return (inside);
	}
	if (is_outside(*(str + i)))
		return (outside);
	else if (is_quote(*(str + i)))
		return (quote);
	else if (is_op(*(str + i)))
		return (op);
	else if (is_may_change(*(str + i)))
		return (may_change);
	else
		return (inside);
}
