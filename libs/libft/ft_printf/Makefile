# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aelouarg <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/20 10:55:39 by aelouarg          #+#    #+#              #
#    Updated: 2019/07/30 02:31:51 by aelouarg         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# This is a minimal set of ANSI/VT100 color codes
_END=$'\x1b[0m
_BOLD=$'\x1b[1m
_UNDER=$'\x1b[4m
_REV=$'\x1b[7m
# Colors
_GREY=$'\x1b[30m
_RED=$'\x1b[31m
_GREEN=$'\x1b[32m
_YELLOW=$'\x1b[33m
_BLUE=$'\x1b[34m
_PURPLE=$'\x1b[35m
_CYAN=$'\x1b[36m
_WHITE=$'\x1b[37m
# Colored backgrounds
_IGREY=$'\x1b[40m
_IRED=$'\x1b[41m
_IGREEN=$'\x1b[42m
_IYELLOW=$'\x1b[43m
_IBLUE=$'\x1b[44m
_IPURPLE=$'\x1b[45m
_ICYAN=$'\x1b[46m
_IWHITE=$'\x1b[47m

PROJECT 	= ft_printf
CC			= gcc
FLAGS		= -Wall -Wextra -Werror
NAME		= libftprintf.a
FILENAMES 	= flags.c\
			float.c\
			float_manager.c\
			float_tools.c\
			ldouble.c\
			ldouble_manager.c\
			ldouble_tools.c\
			ft_printf.c\
			numbers.c\
			numbers2.c\
			strings.c\
			time.c\
			tools.c\
			colors.c\
			non_printable.c\
			tools2.c

OBJ_DIR 	= obj
SRC_DIR		= src
SRC			= $(addprefix $(SRC_DIR)/, $(FILENAMES))
HDR 		= ./includes/printf.h
LIBFT		= src/libft/libft.a
OBJ			=  $(addprefix $(OBJ_DIR)/, $(FILENAMES:.c=.o))

all: $(NAME)

$(NAME):  $(OBJ) | $(LIBFT)
	@cp $(LIBFT) ./$(NAME)
	@ar -cr $(NAME) $(OBJ)

$(OBJ):	$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c $(HDR) | $(OBJ_DIR)
	@$(CC) $(FLAGS) -c $< -o $@ 
	@printf "$(_IYELLOW) $(_END)"

$(LIBFT) : 
	@make -C ./src/libft

$(OBJ_DIR): 
	@mkdir $(OBJ_DIR)

clean:
	@make clean -C ./src/libft
	@rm -rf  $(OBJ_DIR)

fclean: clean
	@make fclean -C ./src/libft
	@rm -f $(NAME)

re: fclean all
