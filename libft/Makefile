# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kgale <kgale@student.21-school.ru>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/02 09:31:56 by kgale             #+#    #+#              #
#    Updated: 2021/04/19 15:56:28 by kgale            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
CC = gcc
FLAGS = -Wall -Wextra -Werror
HEADER = libft.h
OPTION = -c -I $(HEADER)
SRCS_DIR = .
SRCS =		$(SRCS_DIR)/ft_atoi.c	\
			$(SRCS_DIR)/ft_bzero.c	\
			$(SRCS_DIR)/ft_calloc.c	\
			$(SRCS_DIR)/ft_isalnum.c	\
			$(SRCS_DIR)/ft_isalpha.c	\
			$(SRCS_DIR)/ft_isascii.c	\
			$(SRCS_DIR)/ft_isdigit.c	\
			$(SRCS_DIR)/ft_isprint.c	\
			$(SRCS_DIR)/ft_itoa.c	\
			$(SRCS_DIR)/ft_memccpy.c	\
			$(SRCS_DIR)/ft_memcmp.c	\
			$(SRCS_DIR)/ft_memchr.c	\
			$(SRCS_DIR)/ft_memcpy.c	\
			$(SRCS_DIR)/ft_memmove.c	\
			$(SRCS_DIR)/ft_memset.c	\
			$(SRCS_DIR)/ft_putchar_fd.c	\
			$(SRCS_DIR)/ft_putendl_fd.c	\
			$(SRCS_DIR)/ft_putnbr_fd.c	\
			$(SRCS_DIR)/ft_putstr_fd.c	\
			$(SRCS_DIR)/ft_split.c	\
			$(SRCS_DIR)/ft_strchr.c	\
			$(SRCS_DIR)/ft_strdup.c	\
			$(SRCS_DIR)/ft_strjoin.c	\
			$(SRCS_DIR)/ft_strlcat.c	\
			$(SRCS_DIR)/ft_strlen.c	\
			$(SRCS_DIR)/ft_strmapi.c	\
			$(SRCS_DIR)/ft_strncmp.c	\
			$(SRCS_DIR)/ft_strnstr.c	\
			$(SRCS_DIR)/ft_strrchr.c	\
			$(SRCS_DIR)/ft_strtrim.c	\
			$(SRCS_DIR)/ft_substr.c	\
			$(SRCS_DIR)/ft_tolower.c	\
			$(SRCS_DIR)/ft_toupper.c	\
			$(SRCS_DIR)/get_next_line.c \
			$(SRCS_DIR)/get_next_line_utils.c\
			$(SRCS_DIR)/get_next_line_helpers.c

OBJS =		$(SRCS:.c=.o)

SRCS_BON =	$(SRCS_DIR)/ft_lstnew.c\
			$(SRCS_DIR)/ft_lstadd_front.c\
			$(SRCS_DIR)/ft_lstlast.c\
			$(SRCS_DIR)/ft_lstsize.c\
			$(SRCS_DIR)/ft_lstdelone.c\
			$(SRCS_DIR)/ft_lstclear.c\
			$(SRCS_DIR)/ft_lstiter.c\
			$(SRCS_DIR)/ft_lstmap.c

OBJS_BON =	$(SRCS_BON:.c=.o)

all:		$(NAME)

$(NAME):	$(OBJS)
				ar rcs $(NAME) $(OBJS)

clean:
				rm -f $(OBJS) $(OBJS_BON)

fclean:		clean
				rm -f $(NAME)

re:			fclean all

bonus:		$(OBJS) $(OBJS_BON)
				ar rcs $(NAME) $(OBJS) $(OBJS_BON)

.PHONY:	all clean fclean re
