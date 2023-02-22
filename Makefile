# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abouramd <abouramd@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/17 05:30:41 by abouramd          #+#    #+#              #
#    Updated: 2023/02/22 11:40:52 by abouramd         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := minishell

CFLAGS := -Wall -Wextra -Werror -fsanitize=address

INC := -I ./include  -I ./library/libft -I ./library/readline/

LIB := -L ./library/libft/ -L ./library/readline -lreadline -lft -lcurses

BUILTINS:= ./executing/builtins/cd.c ./executing/builtins/echo.c ./executing/builtins/env.c ./executing/builtins/exit.c ./executing/builtins/export.c ./executing/builtins/pwd.c ./executing/builtins/unset.c

SRC_EXEC := $(BUILTINS) main.c ./executing/pipeline.c ./executing/builtins.c ./executing/creat_path.c ./executing/executing.c ./executing/join.c ./executing/put_c.c ./executing/ft_env.c ./executing/sort_string.c ./executing/get_path.c

SRC_PARS := ./parsing/all_is_good.c ./parsing/command_table.c ./parsing/here_documents.c ./parsing/initialize.c ./parsing/join_characters.c ./parsing/open_files.c ./parsing/parse_str.c ./parsing/parsing.c

OBJ := $(SRC_EXEC:.c=.o) $(SRC_PARS:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
#	@echo "\033[1;33m configure readline library ...\033[0m"
#	@echo "\033[1;34m" && cd ./library/readline && ./configure && echo "\033[1;33m ✅ compile readline library ...\033[0m" && make
#	@echo "\033[1;32m ✅ readline library is done.\033[0m"
	@make bonus -C ./library/libft/
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME)  $(INC) $(LIB)
	@echo "\033[1;32m ✅ minishell is done.\033[0m"

	
readline_lib:
	@echo "\033[1;33m configure readline library ...\033[0m"
	@echo "\033[1;34m" && cd ./library/readline && ./configure && echo "\033[1;33m ✅ compile readline library ...\033[0m" && make
	@echo "\033[1;32m ✅ readline library is done.\033[0m"

.c.o:
	@$(CC) $(CFLAGS) -c $< -o $@ $(INC)
	@echo "\033[1;34m - creat $@ from $<.\033[0m"


clean:
#	@echo "\033[1;31m ❎ remove the object files of readline\033[0m"
#	@make clean -C ./library/readline/
	@make clean -C ./library/libft/	
	@echo "\033[1;31m ❎ remove the object files of minishell.\033[0m"
	@rm -rf $(OBJ)
	
fclean: clean
	@rm -rf ./library/libft/libft.a
	@echo "\033[1;31m ❎ remove libft.a\033[0m"
	@echo "\033[1;31m ❎ remove minishell.\033[0m"
	@rm -rf $(NAME)

re: fclean all
