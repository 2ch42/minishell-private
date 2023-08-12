/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junglee <junglee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 16:03:48 by junglee           #+#    #+#             */
/*   Updated: 2023/08/06 17:46:37 by junglee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <stdlib.h>

// atoi
unsigned char	mini_atoi(const char *str);

//itoa
char			*ft_itoa(int n);
//split
void			ft_bzero(void *s, size_t n);
void			*ft_calloc(size_t count, size_t size);
void			*ft_memset(void *b, int c, size_t len);
void			free_split_str(char **split_str);
char			**ft_split(char const *s, char c);

#endif