/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junglee <junglee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 21:12:07 by junglee           #+#    #+#             */
/*   Updated: 2023/08/09 22:09:38 by junglee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include <stdlib.h>

typedef struct s_node			t_node;
typedef struct s_hash_map		t_hash_map;
typedef struct s_list			t_list;

struct	s_node
{
	t_node	*next;
	char	*key;
	char	*value;
	int		equel_sign;
};

struct s_list
{
	t_node	*head;
	int		size;
};

struct	s_hash_map
{
	t_list	linked_list[54];
};

enum	e_valid
{
	VALID,
	INVALID
};

//string_func
size_t	ft_strlen(const char *s);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strdup(const char *s1);
char	*ft_strjoin(char const *s1, char const *s2);

//list_func
void	init_list(t_list *list);
t_node	*key_check(t_list *list, const char *key);
void	change_node(t_node *node, const char *value);
void	add_node(t_list *list, const char *key, const char *value, \
int eq_sign_flag);
void	delete_node(t_list *list, const char *key);

//node_func
t_node	*new_node(const char *key, const char *value, int eq_sign_flag);

//hash_func
void	add_value(t_hash_map *hash_map, const char *key, const char *value, \
int eq_sign_flag);
void	delete_value(t_hash_map *hash_map, const char *key);
char	*get_value(t_hash_map *hash_map, const char *key);
void	hash_map_init(t_hash_map *hash_map, char *envp[]);

//hash_func_utils
void	add_non_value(t_node *node, const char *value, \
int eq_sign_flag);

//export_utils
int		name_valid_check(const char *name);
int		equel_sign_check(const char *name);
void	list_print(t_list *list);

//export_split
char	**export_split(const char *str);

//export
int		mini_export(t_hash_map *hash_map, char *export_arg[]);

//unset
int		mini_unset(t_hash_map *hash_map, char *unset_arg[]);

//env
int		mini_env(t_hash_map *hash_map);

//echo
int		mini_echo(char *echo_arg[]);

//cd
int		mini_cd(t_hash_map *env, char *cd_arg[]);

//pwd
int		mini_pwd(void);

//exit
int		mini_exit(char *exit_arg[]);

//builtin_err
void	cd_found_err(const char *path);
void	cd_not_dir_err(const char *path);
void	cd_permission_err(const char *path);

#endif
