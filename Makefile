# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zasabri <zasabri@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/17 05:30:41 by abouramd          #+#    #+#              #
#    Updated: 2023/03/11 10:45:30 by zasabri          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := minishell

CFLAGS := -Wall -Wextra -Werror #-fsanitize=address -g3

LIB_DIR := libft/ get_next_line/

READLINE_PATH:= ./library/readline

INC := -I ./include $(addprefix -I ./library/,$(LIB_DIR)) -I $(READLINE_PATH)

LIB := $(addprefix -L ./library/,$(LIB_DIR)) -L $(READLINE_PATH) -lreadline -lft -lcurses

BUILTINS := cd.c echo.c env.c exit.c export.c pwd.c unset.c

EXEC_DIR := $(addprefix builtins/, $(BUILTINS)) builtins.c creat_path.c exec_cmd.c executing.c fd_manage.c ft_env.c get_path.c here_doc.c put_c.c sort_string.c signal_handler.c expand.c expand_str.c

SRC_EXEC :=  main.c $(addprefix ./executing/, $(EXEC_DIR)) $(addprefix ./library/get_next_line/,get_next_line.c get_next_line_utils.c)

SRC_PARS := ./parsing/check_hdk_limit.c ./parsing/syntax_error.c ./parsing/command_table.c ./parsing/here_documents.c ./parsing/initialize.c ./parsing/join_characters.c ./parsing/open_files.c ./parsing/parsing.c

OBJ := $(SRC_EXEC:.c=.o) $(SRC_PARS:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
#	@echo "\033[1;33m configure readline library ...\033[0m"
#	@echo "\033[1;34m" && cd ./library/readline && ./configure && echo "\033[1;33m ✅ compile readline library ...\033[1;34m" && make
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
