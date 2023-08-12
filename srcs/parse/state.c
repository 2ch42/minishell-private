/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junglee <junglee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 19:43:24 by changhyl          #+#    #+#             */
/*   Updated: 2023/08/04 19:44:11 by junglee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "token.h"

int	is_outside(char c)
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

t_state	check_st(t_tk *tk, char c)
{
	if (tk != NULL)
	{
		if (tk->single_q % 2 == 1 && c != '\'')
			return (inside);
		if (tk->double_q % 2 == 1 && c != '\"')
			return (inside);
	}
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
