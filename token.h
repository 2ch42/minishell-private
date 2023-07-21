/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: changhyl <changhyl@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 20:41:21 by changhyl          #+#    #+#             */
/*   Updated: 2023/07/21 16:11:10 by changhyl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

typedef enum e_tk_st
{
	outside = 1,
	inside = 2,
	quote = 3,
	op = 4,
	may_change = 5
}	t_tk_st;

typedef struct s_tk
{
	char	*str;
	t_tk	*next;
	int		errno;
}	t_tk;

typedef struct	s_tk_list
{
	t_tk	*head;
	t_tk	*tail;
	int		errno;
}	t_tk_list;

#endif
