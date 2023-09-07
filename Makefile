# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jquil <jquil@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/19 11:08:46 by jugingas          #+#    #+#              #
#    Updated: 2023/09/07 12:18:09 by jquil            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC		=		src/main.c					\
				src/utils.c					\
				src/utils2.c				\
				src/builtins.c				\
				src/builtins2.c				\
				src/ft_split.c				\
				src/export.c				\
				src/ft_strdup.c				\
				src/single_double_quote.c	\
				src/signals.c				\

NAME		=	minishell
OBJS		=	$(SRC:.c=.o)
LIBS		=	-lreadline
CC			=	cc
FLAGS		=	-g3 -Werror -Wextra -Wall

#------------------------------------------------------------------

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(LIBS) -o $(NAME)

%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS) $(DEPS)

fclean: clean
	rm -rf $(NAME)

re:
	$(MAKE) fclean
	$(MAKE) all

#------------------------------------------------------------------

.PHONY: clean fclean re
