# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jugingas <jugingas@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/19 11:08:46 by jugingas          #+#    #+#              #
#    Updated: 2023/09/28 10:20:12 by jugingas         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC		=		src/main.c					\
				src/utils.c					\
				src/utils2.c				\
				src/utils3.c				\
				src/builtins.c				\
				src/builtins2.c				\
				src/ft_split.c				\
				src/export.c				\
				src/env.c					\
				src/ft_strdup.c				\
				src/single_double_quote.c	\
				src/signals.c				\
				src/pipe.c					\
				src/pipe2.c					\
				src/redirections.c			\
				src/get_heredoc.c			\

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
