# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: user42 <user42@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/19 11:08:46 by jugingas          #+#    #+#              #
#    Updated: 2023/07/19 09:58:00 by user42           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC		=		src/main.c				\
				src/utils.c				\
				src/utils2.c			\
				src/builtins.c			\
				src/ft_split.c			\
				src/export.c			\
				src/ft_strdup.c

NAME		=	minishell
OBJS		=    $(SRC:.c=.o)
LIBS		=    -lreadline
CC			=    cc
FLAGS		=    -g3 -Werror -Wextra -Wall

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
