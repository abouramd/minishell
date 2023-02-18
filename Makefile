# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zasabri <zasabri@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/04 19:29:40 by abouramd          #+#    #+#              #
#    Updated: 2023/02/18 00:41:12 by zasabri          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := minishell

CC := cc

CFLAGS := -Wall -Wextra -Werror

INC := -I ./include  -I ./libft

LIB := -lreadline -L ./libft/ -lft

SRC_EXEC := ./executing/executing.c

SRC_PARS := ./parsing/parsing.c\
			./parsing/initialize.c\
			./parsing/all_is_good.c\
			./parsing/parse_str.c\
			./parsing/join_characters.c\
			./parsing/command_table.c\
			./parsing/open_files.c\
			

PROG	= minishell

OBJ := $(SRC_EXEC:.c=.o) $(SRC_PARS:.c=.o)

all:$(NAME)

$(NAME): $(OBJ)
	make bonus -C ./libft/
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)  $(INC) $(LIB)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@ $(INC)


clean:
	make clean -C ./libft/
	rm -rf $(OBJ)
	
fclean: clean
	make fclean -C ./libft/
	rm -rf $(NAME)

re: fclean all
