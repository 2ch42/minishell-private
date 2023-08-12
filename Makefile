# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: junglee <junglee@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/08 15:49:32 by junglee           #+#    #+#              #
#    Updated: 2023/08/12 16:42:38 by ch               ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror
DEBUG_FLAGS = -g
SRCS_DIR = srcs
INCLUDES = includes

SRCS_BUILTIN = $(addprefix builtin/, export_split.c export_utils.c export.c \
								cd.c echo.c env.c exit.c pwd.c unset.c \
								hash_func.c hash_func_utils.c list_func.c mini_string_func.c node_func.c builtin_err.c)

SRCS_EXECUTOR = $(addprefix executor/, cmdfile_path_check.c executor_utils.c executor_utils2.c exit_error.c \
								here_doc_utils.c here_doc_utils2.c mini_executor.c pipe_redirect.c redirect.c \
								std_inout_redirect.c regen_close_pipe.c token_to_word_arg.c wait_child.c)

SRCS_PARSE = $(addprefix parse/, expand_utils.c expand.c expand2.c init_token.c \
							state.c syntax_utils.c syntax.c token_mem.c token_utils.c token.c)

SRCS_SIG = $(addprefix signal/, sig_handle.c)

SRCS_WRAPPING = $(addprefix wrapping/, wrapping_func.c wrapping_func2.c wrapping_func3.c)

SRCS_UTILS = $(addprefix utils/atoi/, mini_atoi.c) \
				$(addprefix utils/get_next_line/, get_next_line_bonus.c get_next_line_utils_bonus.c) \
				$(addprefix utils/itoa/, ft_itoa.c) \
				$(addprefix utils/split/, ft_bzero.c ft_calloc.c ft_memset.c ft_split.c)

SRCS = $(addprefix $(SRCS_DIR)/, $(SRCS_BUILTIN) $(SRCS_EXECUTOR) $(SRCS_PARSE) $(SRCS_SIG) $(SRCS_WRAPPING) main.c ) \
		$(SRCS_UTILS)

OBJS = $(SRCS:.c=.o)

$(NAME) :: $(OBJS)
	$(CC) $(CFLAGS) -I. -L/opt/homebrew/opt/readline/lib -o $(NAME) $^ $(DEBUG_FLAGS) -lreadline

all : $(NAME)

%.o : %.c
	$(CC) $(CFLAGS) -c -I. -I$(INCLUDES) -I/opt/homebrew/opt/readline/include $< $(DEBUG_FLAGS) -o $@

clean :
	rm -rf $(OBJS)

fclean : clean
	rm -rf $(NAME)

re :
	make fclean
	make all

.PHONY : all clean fclean re
