# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abouramd <abouramd@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/17 05:30:41 by abouramd          #+#    #+#              #
#    Updated: 2023/02/19 09:27:17 by abouramd         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := minishell

CFLAGS := #-Wall -Wextra -Werror

INC := -I ../include  -I ./library/libft -I ./library/readline/

LIB := -L ./library/libft/ -L ./library/readline -lreadline -lft -lcurses

SRC_EXEC := builtins.c creat_path.c executing.c join.c put_c.c ft_env.c

SRC_PARS := 

OBJ := $(SRC_EXEC:.c=.o) $(SRC_PARS:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	make bonus -C ./library/libft/
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)  $(INC) $(LIB)

	
readline_lib:
	cd ./library/readline && ./configure && make

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@ $(INC)


clean:
	rm -rf $(OBJ)
# make fclean -C ./library/libft/	
# make clean -C ./library/readline/
	
fclean: clean
	rm -rf $(NAME)
# make fclean -C ./library/libft/

re: fclean all
