/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_handle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: changhyl <changhyl@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 18:30:42 by changhyl          #+#    #+#             */
/*   Updated: 2023/08/09 21:21:55 by changhyl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <sig.h>
#include <readline/readline.h>
#include <readline/history.h>

static void	sig_handle(int signal)
{
	if (signal == SIGINT)
	{
		g_exit_code = 1;
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (signal == SIGQUIT)
	{
		rl_on_new_line();
		rl_redisplay();
	}
}

void	sig_handler(int sig_int, int sig_quit)
{
	if (sig_int == DEFAULT)
		signal(SIGINT, SIG_DFL);
	if (sig_int == IGNORE)
		signal(SIGINT, SIG_IGN);
	if (sig_int == PROMPT)
		signal(SIGINT, sig_handle);
	if (sig_quit == DEFAULT)
		signal(SIGQUIT, SIG_DFL);
	if (sig_quit == IGNORE)
		signal(SIGQUIT, SIG_IGN);
	if (sig_quit == PROMPT)
		signal(SIGQUIT, sig_handle);
}
