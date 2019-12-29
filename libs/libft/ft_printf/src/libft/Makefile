# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aelouarg <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/20 09:19:51 by aelouarg          #+#    #+#              #
#    Updated: 2019/07/30 02:51:48 by aelouarg         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# This is a minimal set of ANSI/VT100 color codes
_END=$'\x1b[0m
_BOLD=$'\x1b[1m
_UNDER=$'\x1b[4m
_BLINK=$'\x1b[5m
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

PROJECT 	= libft
CC			= gcc
FLAGS		= -Wall -Wextra -Werror
NAME		= libft.a
FILENAMES 	= ft_atoi.c ft_bzero.c ft_count_words.c ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isblank.c ft_iscntrl.c ft_isdigit.c ft_isgraph.c ft_isprint.c ft_isxdigit.c ft_itoa.c ft_itoa_base.c ft_lstadd.c \
		   	ft_lstcount.c ft_lstdel.c ft_lstdelone.c ft_lstiter.c ft_lstmap.c ft_lstnew.c ft_memalloc.c ft_memccpy.c ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memdel.c ft_memmove.c ft_memset.c ft_putchar.c \
			ft_putchar_fd.c ft_putendl.c ft_putendl_fd.c ft_putnbr.c ft_putnbr_fd.c ft_putstr.c ft_putstr_fd.c ft_sqrt.c ft_str_pushback.c ft_strcapitalize.c ft_strcasecmp.c ft_strcat.c ft_strccut.c ft_strchr.c \
		   	ft_strclr.c ft_strcmp.c ft_strcnew.c ft_strcpy.c ft_strdel.c ft_strdup.c ft_strequ.c ft_strfreesub.c ft_striter.c ft_striteri.c ft_strjoin.c ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strmap.c \
		   	ft_strmapi.c ft_strmult.c ft_strncat.c ft_strncmp.c ft_strncpy.c ft_strndup.c ft_strnequ.c ft_strnew.c ft_strnstr.c ft_strpower.c ft_strrchr.c ft_strrev.c ft_strsplit.c ft_strstr.c ft_strsub.c \
		   	ft_strsum.c ft_strswap.c ft_strtrim.c ft_tolower.c ft_toupper.c
OBJ_DIR 	= obj
HDR 	=  libft.h
OBJ		=  $(addprefix $(OBJ_DIR)/, $(FILENAMES:.c=.o))

all: $(NAME)

$(NAME): $(OBJ)
	@ar rc $(NAME) $(OBJ)
	@echo " ${_CYAN}${_BOLD}${_UNDER}libft.a${_END} created $(_IYELLOW)   $(_END)"

$(OBJ):	$(OBJ_DIR)/%.o : %.c $(HDR) | $(OBJ_DIR)
	@$(CC) $(FLAGS) -c $< -o $@
	@printf "$(_IYELLOW) $(_END)"

$(OBJ_DIR): 
	@mkdir $(OBJ_DIR)

clean:
	@rm -rf  $(OBJ_DIR)
	@echo "${_RED}${_BOLD}Cleaning $(PROJECT) objects.${_END}"

fclean: clean
	@rm -f $(NAME)
	@echo "${_RED}${_BOLD}${_UNDER}libft.a${_END} deleted."

re: fclean all
