# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abiri <kerneloverseer@pm.me>               +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/12/29 18:57:44 by abiri             #+#    #+#              #
#    Updated: 2019/12/29 20:17:51 by abiri            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
FLAGS = -Wall -Werror -Wextra

include ./assembler/assembler.mk
include ./virtual_machine/virtual_machine.mk

.PHONY: all
all: $(VIRTUAL_MACHINE_NAME) $(ASSEMBLER_NAME)

.PHONY: clean
clean: virtual_machine_clean assembler_clean

.PHONY: fclean
fclean: virtual_machine_fclean assembler_fclean

.PHONY: re
re: fclean all
