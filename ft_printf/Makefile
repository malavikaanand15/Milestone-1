# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: manand <manand@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/09/08 12:58:09 by manand            #+#    #+#              #
#    Updated: 2026/09/08 18:41:40 by manand           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

Name	= libftprintf.a
CC		= cc
CFLAGS	= -Wall -Wextra -Werror

SRCS	= 	ft_printf.c ft_printf_utils.c

OBJS	= $(SRCS:.c=.o)

all: $(NAME)

%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean:
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re