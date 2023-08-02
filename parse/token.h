/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: changhyl <changhyl@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 20:41:21 by changhyl          #+#    #+#             */
/*   Updated: 2023/08/02 19:00:49 by changhyl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

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
	int			new_sig;
	t_tktype	tktype;
	struct s_tk	*next;
}	t_tk;

typedef struct s_tk_list
{
	t_tk	*head;
	t_tk	*tail;
}	t_tk_list;

size_t		tk_strlen(const char *s);
char		*tk_strjoin(t_tk *tk, char s2);
t_tk_list	*init_tk_list(void);
t_tk		*init_tk(void);
t_state		check_st(t_tk *tk, char c);
void		tk_clear(t_tk_list *tk_list);
t_tk_list	*tokenize(char *str);
void		syn_err_nl(t_tk_list *tk_list);
void		syn_err_nnl(char *str, t_tk_list *tk_list);
void		fill_tktype(t_tk_list *tk_list);
t_tk_list	*check_syntax(char *str);

#endif
