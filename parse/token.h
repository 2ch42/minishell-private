/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: changhyl <changhyl@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 20:41:21 by changhyl          #+#    #+#             */
/*   Updated: 2023/07/28 20:34:52 by changhyl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

# include <stdlib.h>

typedef enum e_state
{
	outside = 1,
	inside = 2,
	quote = 3,
	op = 4,
	may_change = 5
}	t_state;

typedef enum e_tktype
{
	word = 1,
	redirect_l = 2,
	redirect_r = 3,
	heredoc = 4,
	append = 5,
	pipeline = 6
}	t_tktype;

typedef struct s_tk
{
	char		*str;
	int			single_q;
	int			double_q;
	int			redirect_l;
	int			redirect_r;
	int			pipeline;
	t_tktype	tktype;
	struct s_tk	*next;
}	t_tk;

typedef struct s_tk_list
{
	t_tk	*head;
	t_tk	*tail;
}	t_tk_list;

size_t		tk_strlen(const char *s);
char		*tk_strjoin(char *s1, char s2);
t_tk_list	*init_tk_list(void);
t_tk		*init_tk(void);
t_state		check_st(t_tk *tk, char c);
void		tk_clear(t_tk_list *tk_list);
t_tk_list	*tokenize(char *str);
t_tk_list	*check_syntax(char *str);

#endif
