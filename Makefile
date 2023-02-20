# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abouramd <abouramd@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/17 05:30:41 by abouramd          #+#    #+#              #
#    Updated: 2023/02/20 02:31:59 by abouramd         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := minishell

CFLAGS := #-Wall -Wextra -Werror

INC := -I ./include  -I ./library/libft -I ./library/readline/

LIB := -L ./library/libft/ -L ./library/readline -lreadline -lft -lcurses

SRC_EXEC := main.c ./executing/builtins.c ./executing/creat_path.c ./executing/executing.c ./executing/join.c ./executing/put_c.c ./executing/ft_env.c

SRC_PARS := ./parsing/all_is_good.c ./parsing/command_table.c ./parsing/here_documents.c ./parsing/initialize.c ./parsing/join_characters.c ./parsing/open_files.c ./parsing/parse_str.c ./parsing/parsing.c

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
	make fclean -C ./library/libft/	
	make clean -C ./library/readline/
	rm -rf $(OBJ)
	
fclean: clean
	make fclean -C ./library/libft/
	rm -rf $(NAME)

re: fclean all
