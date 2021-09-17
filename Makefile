# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kgale <kgale@student.21-school.ru>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/11 20:31:15 by kgale             #+#    #+#              #
#    Updated: 2021/09/11 20:31:15 by kgale            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = gcc
FLAGS = -Wall -Wextra -Werror
LIB = libft/libft.a
LIBFT = make bonus -C libft
SRCS =  array_handler.c \
		cd.c \
		dbl_qts_handle.c \
		echo.c \
		env.c \
		executable.c \
		exec.c \
		exec_init_utils.c \
		exec_init.c \
		export.c \
		get_line_from_term.c \
		handle_dollar.c \
		handle_symbols.c \
		minishell.c \
		pwd.c \
		redir.c \
		symb_handle.c \
		terminal_management.c \
		unset.c

HEADER = minishell.h
INCLUDE = -I includes

OBJS_SRCS = ${SRCS:.c=.o}

%.o: %.c
		${CC} ${FLAGS} ${INCLUDE} -c $< -o $(<:.c=.o)

all: $(NAME)

$(NAME) : $(OBJS_SRCS)
		@$(LIBFT)
		@$(CC) -o $(NAME) $(OBJS_SRCS) $(LIB) $(INCLUDE) -ltermcap

clean:
		@rm -f $(OBJS_SRCS)
		@$(LIBFT) clean

fclean: clean
		@rm -f $(NAME)
		@$(LIBFT) fclean

re: fclean all

.PHONY: all clean fclean re
