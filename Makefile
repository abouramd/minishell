# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abouramd <abouramd@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/17 05:30:41 by abouramd          #+#    #+#              #
#    Updated: 2023/02/22 12:11:39 by abouramd         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := minishell

CFLAGS := -Wall -Wextra -Werror -fsanitize=address

LIB_DIR := libft/ readline/

INC := -I ./include $(addprefix -I ./library/,$(LIB_DIR))

LIB := $(addprefix -L ./library/,$(LIB_DIR)) -lreadline -lft -lcurses

BUILTINS := cd.c echo.c env.c exit.c export.c pwd.c unset.c

EXEC_DIR := $(addprefix builtins/, $(BUILTINS)) pipeline.c builtins.c creat_path.c executing.c join.c put_c.c ft_env.c sort_string.c get_path.c

SRC_EXEC :=  main.c $(addprefix ./executing/, $(EXEC_DIR))

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
