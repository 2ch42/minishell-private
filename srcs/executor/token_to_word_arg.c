/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_to_word_arg.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junglee <junglee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 20:18:40 by junglee           #+#    #+#             */
/*   Updated: 2023/08/08 18:50:54 by junglee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "wrapping.h"

static int	word_count(t_tk *token)
{
	int	cnt;

	cnt = 0;
	while (token && token->tktype != pipeline)
	{
		if (token->tktype == word)
			cnt++;
		if (token->tktype == redirect_l || token->tktype == redirect_r \
		|| token->tktype == heredoc || token->tktype == append)
			token = token->next;
		token = token->next;
	}
	return (cnt);
}

static void	put_word(t_tk *token, char **word_arg)
{
	int	i;

	i = 0;
	while (token && token->tktype != pipeline)
	{
		if (token->tktype == word)
			word_arg[i++] = ft_strdup(token->str);
		if (token->tktype == redirect_l || token->tktype == redirect_r \
		|| token->tktype == heredoc || token->tktype == append)
			token = token->next;
		token = token->next;
	}
	word_arg[i] = 0;
}

t_tk	*token_move_to_pipe(t_tk *token, int i)
{
	t_tk	*temp;

	temp = token;
	if (i == 0)
		return (temp);
	while (temp && temp->tktype != pipeline)
		temp = temp->next;
	if (temp != NULL)
		temp = temp->next;
	return (temp);
}

char	**tk_redirect(t_tk *token, int std_fd[2], int *file_status)
{
	char	**word_arg;

	word_arg = (char **)malloc_s(sizeof(char *) * (word_count(token) + 1));
	put_word(token, word_arg);
	while (token && token->tktype != pipeline)
	{
		if (token->tktype == redirect_l || token->tktype == heredoc)
			redirect_left(token->next->str, &std_fd[IN], file_status);
		else if (token->tktype == redirect_r)
			redirect_right(token->next->str, &std_fd[OUT], file_status);
		else if (token->tktype == append)
			redirect_append(token->next->str, &std_fd[OUT], file_status);
		if (*file_status > 0)
			return (0);
		token = token->next;
	}
	return (word_arg);
}
