# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kgale <kgale@student.21-school.ru>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/15 01:41:01 by dwanetta          #+#    #+#              #
#    Updated: 2021/04/26 13:02:16 by kgale            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = gcc
FLAGS = #-Wall -Wextra -Werror
LIB = -L libft
OPTION_LIB = -lft -lreadline
OPTION = -c
LIBFT = make -C libft
SRCS =	main.c line_parse.c

OBJS_SRCS = ${SRCS:.c=.o}

all: $(NAME)

$(NAME) : $(OBJS_SRCS)
		@$(CC) $(FLAGS) $(OPTION) -I./includes $(SRCS)
		@$(LIBFT)
		@$(MLX)
		$(CC) $(OBJS_SRCS) -o $(NAME) $(LIB) $(OPTION_LIB)
clean:
		rm -f $(OBJS_SRCS)
		@$(LIBFT) clean
fclean: clean
		rm -f $(NAME)
		@$(LIBFT) fclean
re: fclean all
.PHONY: all clean fclean re
