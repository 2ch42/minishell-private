/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junglee <junglee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 17:23:19 by junglee           #+#    #+#             */
/*   Updated: 2023/08/09 23:49:27 by changhyl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"
#include "builtin.h"
#include "executor.h"
#include "sig.h"
#include <unistd.h>
#include <stdio.h>
#include <termios.h>
#include <readline/readline.h>
#include <readline/history.h>

static void			check_init(int argc, char *argv[], t_hash_map *env, \
		char *envp[]);
static t_tk_list	*check_str(char *str, t_hash_map *env);

int	main(int argc, char *argv[], char *envp[])
{
	t_tk_list	*tk_list;
	t_hash_map	env;
	char		*str;

	check_init(argc, argv, &env, envp);
	while (1)
	{
		g_exit_code = 0;
		sig_handler(PROMPT, PROMPT);
		str = readline("minishell: ");
		if (g_exit_code == 1)
			add_value(&env, "?", "1", 0);
		tk_list = check_str(str, &env);
		if (tk_list && is_outside(*str) == 0)
			mini_execute(tk_list, &env, envp);
		if (tk_list)
			tk_clear(tk_list);
		free(str);
	}
	return (0);
}

static void	check_init(int argc, char *argv[], t_hash_map *env, char *envp[])
{
	struct termios	term;

	if (argc != 1)
	{
		file_not_found_err(argv[1]);
		exit(127);
	}
	tcgetattr(0, &term);
	term.c_lflag &= ~ECHOCTL;
	tcsetattr(0, TCSANOW, &term);
	hash_map_init(env, envp);
}

static t_tk_list	*check_str(char *str, t_hash_map *env)
{
	t_tk_list	*tk_list;

	tk_list = NULL;
	if (!str)
	{
		write(1, "exit\n", 5);
		exit(0);
	}
	if (*str)
	{
		add_history(str);
		tk_list = mini_expand(str, env);
	}
	return (tk_list);
}
