/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junglee <junglee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 18:36:32 by changhyl          #+#    #+#             */
/*   Updated: 2023/08/09 22:11:39 by junglee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIG_H
# define SIG_H

# ifndef DEFAULT
#  define DEFAULT 0
# endif

# ifndef IGNORE
#  define IGNORE 1
# endif

# ifndef PROMPT
#  define PROMPT 2
# endif

int		g_exit_code;
void	sig_handler(int sig_int, int sig_quit);

#endif
