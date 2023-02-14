# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zasabri <zasabri@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/04 19:29:40 by abouramd          #+#    #+#              #
#    Updated: 2023/02/14 02:30:00 by zasabri          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := minishell

CC := cc

CFLAGS := -Wall -Wextra -Werror

INC := -I ./include

LIB := -lreadline

SRC_EXEC :=

SRC_PARS := ./parsing/parsing.c\
			./include/libft/ft_strlen.c\
			./include/libft/ft_strjoin.c\
			./include/libft/ft_lstadd_back_bonus.c\
			./include/libft/ft_lstlast_bonus.c\
			./include/libft/ft_lstnew_bonus.c\
			./parsing/initialize.c\
			./parsing/all_is_good.c\
			

PROG	= minishell

OBJ := $(SRC_EXEC:.c=.o) $(SRC_PARS:.c=.o)

all:$(NAME)

$(NAME):$(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)  $(INC) $(LIB)

# $(OBJ): $(SRC_EXEC) $(SRC_PARS)
# 	$(CC) $(CFLAGS) $(SRC_EXEC) $(SRC_PARS) $(LIB) -o $(PROG)
	

clean:
	rm -rf $(OBJ)
	
fclean: clean
	rm -rf $(NAME)

re: fclean all
