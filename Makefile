# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abiri <abiri@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/12/29 18:57:44 by abiri             #+#    #+#              #
#    Updated: 2020/02/06 16:19:47 by abiri            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
FLAGS = -Wall -Werror -Wextra

.PHONY: all
all: main

include ./libraries_linking.mk
include ./assembler/assembler.mk
include ./virtual_machine/virtual_machine.mk

# MAIN RULES

.PHONY: main
main: libft $(VIRTUAL_MACHINE_NAME) $(ASSEMBLER_NAME)

.PHONY: clean
clean: virtual_machine_clean assembler_clean libft_clean

.PHONY: fclean
fclean: virtual_machine_fclean assembler_fclean libft_fclean

.PHONY: re
re: fclean all
