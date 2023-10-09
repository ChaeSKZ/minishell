# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jquil <jquil@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/19 11:08:46 by jugingas          #+#    #+#              #
#    Updated: 2023/10/09 15:11:08 by jquil            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC		=		src/main.c					\
				src/main_functions.c		\
				src/utils.c					\
				src/utils2.c				\
				src/utils3.c				\
				src/utils4.c				\
				src/builtins.c				\
				src/builtins2.c				\
				src/ft_split.c				\
				src/export.c				\
				src/env.c					\
				src/env2.c					\
				src/ft_strdup.c				\
				src/single_double_quote.c	\
				src/single_double_quote2.c	\
				src/signals.c				\
				src/pipe.c					\
				src/pipe2.c					\
				src/pipe3.c					\
				src/redirections.c			\
				src/get_heredoc.c			\
				src/init_struct.c

NAME		=	minishell
OBJS		=	$(SRC:.c=.o)
LIBS		=	-lreadline
CC			=	cc
FLAGS		=	-g3 -Werror -Wextra -Wall -I include

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
