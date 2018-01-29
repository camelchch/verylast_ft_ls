# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fsabatie <fsabatie@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/06 21:06:58 by fsabatie          #+#    #+#              #
#    Updated: 2018/01/24 14:13:35 by saxiao           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Protecting makefile
.PHONY: all clean fclean re

# Defining variables
NAME = ft_ls

#SRC_PATH = srcs
#INC_PATH = includes

SRC =	creat_dic.c get_dirlt_inclu.c incb_deladdlist.c\
			init_lformat.c main.c put_bigr_eachdic.c \
			put_color.c put_dirname.c put_list.c sort_rev_list.c\
			for_others.c for_longfuncs.c

LIB_NAME = libft.a
PRINTF_NAME = libftprintf.a
LIB_PATH = libft
OBJ = $(SRC:.c=.o)

#SRC = $(addprefix $(SRC_PATH)/,$(SRC_NAME))
#LIB = $(addprefix $(INC_PATH)/,$(LIB_PATH))
LIBFT = $(addprefix $(LIB_PATH)/,$(LIB_NAME))
PRINTF = $(addprefix $(LIB_PATH)/,$(PRINTF_NAME))
CPPFLAGS = -Wall -Werror -Wextra -I.

# Defining colors

RED = \033[1;31m
GREEN = \033[0;32m
ORANGE = \033[0;33m
BLUE = \033[1;36m
YELLOW = \033[1;33m
PURPLE = \033[1;35m
NC = \033[0m

# Defining rules

all: $(NAME)

$(NAME):
	@echo "${GREEN}Compiling libft." | tr -d '\n'
	@cd $(LIB_PATH) && make re
	@echo " ${GREEN}Done."
	@cd ..
	@echo "${GREEN}Compiling ft_ls" | tr -d '\n'
	@gcc $(CPPFLAGS) -c $(SRC)
	@gcc $(CPPFLAGS) $(OBJ) $(LIBFT) $(PRINTF) -o $(NAME)
	@echo " ${GREEN}Done."

clean:
	@rm -rf $(OBJ)
	@cd $(LIB_PATH) && make clean
	@cd ..

fclean: clean
	@rm -rf $(NAME)
	@cd $(LIB_PATH) && make fclean
	@cd ..

re: fclean all
