/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junglee <junglee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 20:41:21 by changhyl          #+#    #+#             */
/*   Updated: 2023/08/07 14:22:32 by changhyl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

# include <stdlib.h>
# include "builtin.h"

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
int			is_ad(char c);
char		*tk_strjoin(t_tk *tk, char s2);
t_tk_list	*init_tk_list(void);
t_tk		*init_tk(void);
t_state		check_st(t_tk *tk, char c);
void		tk_clear(t_tk_list *tk_list);
t_tk_list	*tokenize(char *str);
void		syn_err_nl(t_tk_list *tk_list, t_hash_map *hash_map);
void		syn_err_nnl(char *str, t_tk_list *tk_list, t_hash_map *hash_map);
void		fill_tktype(t_tk_list *tk_list);
char		*make_exp_key(t_tk *tk, int idx);
t_tk_list	*check_syntax(char *str, t_hash_map *hash_map);
t_tk_list	*mini_expand(char *str, t_hash_map *hash_map);
int			is_outside(char c);
void		del_q(t_tk *tk);

#endif
