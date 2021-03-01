# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fgalaup <fgalaup@student.42lyon.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/05 14:25:53 by fgalaup           #+#    #+#              #
#    Updated: 2021/02/17 11:33:22 by fgalaup          ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

# Project vars
NAME			=		minishell

SRCS			=		./srcs/minishell.c \
						./srcs/utilities/path.c \
						./srcs/utilities/debug.c \
						./srcs/utilities/error.c \
						./srcs/utilities/environment.c \
						./srcs/test/path.c

HEADER_DIR		=		./srcs/

HEADER			=		./srcs/minishell.h \
						./srcs/minishell_type.h \
						./srcs/minishell_utilities.h \
						./srcs/minishell_error.h \
						./srcs/minishell_builtin.h \
						./srcs/minishell_scheduler.h



# Libs (Libft)

LIBFT_DIR		=		libs/Libft
LIBFT_HEADER	=		$(LIBFT_DIR)
LIBFT			=		$(LIBFT_DIR)/libft.a

# Workings vars
CC				=		gcc
CFLAGS			=		-Wall -Wextra -Werror -g3 -fsanitize=address
CMLXFLAGS		=		

RM				=		rm -f
OBJS			=		$(SRCS:.c=.o)

all:	$(NAME)

$(NAME): libft $(OBJS) $(HEADER)
		$(CC) $(CFLAGS) $(LIBFT) $(CMLXFLAGS) $(OBJS) -o $(NAME)

bonus: $(NAME)

libft:
		$(MAKE) -C $(LIBFT_DIR) all

norminette:
		$(MAKE) -C $(LIBFT_DIR) norminette
		norminette $(SRCS) $(HEADER)


%.o: %.c $(HEADER)
		$(CC) $(CFLAGS) -I $(LIBFT_HEADER) -I $(HEADER_DIR) -c $< -o $@

clean:
		$(RM) $(OBJS)
		$(MAKE) -C $(LIBFT_DIR) fclean

fclean: clean
		$(RM) $(NAME)
		$(MAKE) -C $(LIBFT_DIR) fclean

re:	fclean all

.PHONY:			all libft re bonus clean fclean