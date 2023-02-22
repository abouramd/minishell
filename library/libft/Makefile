# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abouramd <abouramd@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/06 13:08:41 by abouramd          #+#    #+#              #
#    Updated: 2023/02/21 03:23:27 by abouramd         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME:= libft.a

SRC:= ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c ft_itoa.c ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c ft_split.c ft_strchr.c ft_strdup.c ft_striteri.c ft_strjoin.c ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strmapi.c ft_strncmp.c ft_strnstr.c ft_strrchr.c ft_strtrim.c ft_substr.c ft_tolower.c ft_toupper.c

SBONUS:= ft_lstadd_back_bonus.c ft_lstadd_front_bonus.c ft_lstlast_bonus.c ft_lstnew_bonus.c ft_lstsize_bonus.c ft_lstdelone_bonus.c ft_lstclear_bonus.c ft_lstiter_bonus.c ft_lstmap_bonus.c

OBJ:= $(SRC:.c=.o)

OBONUS:= $(SBONUS:.c=.o)

CC:= cc

CFLAGS:= -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJ)

bonus: $(OBJ) $(OBONUS)

.c.o:
	@$(CC) $(CFLAGS) -c $<
	@echo "\033[1;34m - creat $@ from $<.\033[0m"
	@ar -crs $(NAME) $@
	@echo "\033[1;34m - add $@ to $(NAME).\033[0m"
	

$(OBONUS):$(SBONUS)
	@$(CC) $(CFLAGS) -c $(SBONUS)
	@ar -crs $(NAME) $(OBONUS)
	@echo "\033[1;32m ✅ libft is done.\033[0m"

clean:
	@rm -f $(OBONUS) $(OBJ)
	@echo "\033[1;31m ❎ remove the object files of libft.\033[0m"

fclean: clean
	@rm -f $(NAME)
	@echo "\033[1;31m ❎ remove libft.a\033[0m"

re: fclean all
