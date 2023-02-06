# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abouramd <abouramd@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/04 19:29:40 by abouramd          #+#    #+#              #
#    Updated: 2023/02/04 19:29:41 by abouramd         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := minishell

CC := cc

CFLAGS := -Wall -Wextra -Werror

INC := -I ./include

SRC_EXEC :=

SRC_PARS :=

OBJ := $(SRC_EXEC:.c=.o) $(SRC_PARS:.c=.o)

all:$(NAME)

$(NAME):$(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(INC)

clean:
	rm -rf $(OBJ)
	
fclean: clean
	rm -rf $(NAME)

re: fclean all
