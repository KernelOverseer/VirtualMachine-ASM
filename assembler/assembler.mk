# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    assembler.mk                                       :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abiri <kerneloverseer@pm.me>               +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/12/29 17:57:31 by abiri             #+#    #+#              #
#    Updated: 2019/12/29 20:16:12 by abiri            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# EDIT ONLY HERE

ASSEMBLER_DIR = ./assembler
ASSEMBLER_NAME = asm
ASSEMBLER_SRC_NAMES = main.c

# AUTOMATIC PART

ASSEMBLER_NAME := $(ASSEMBLER_DIR)/$(ASSEMBLER_NAME)
ASSEMBLER_SRC_DIR = $(ASSEMBLER_DIR)/sources
ASSEMBLER_INC_DIR = $(ASSEMBLER_DIR)/includes
ASSEMBLER_OBJ_DIR = $(ASSEMBLER_DIR)/objects
ASSEMBLER_SRC = $(addprefix $(ASSEMBLER_SRC_DIR)/, $(ASSEMBLER_SRC_NAMES))
ASSEMBLER_OBJ = $(addprefix $(ASSEMBLER_OBJ_DIR)/, $(ASSEMBLER_SRC_NAMES:.c=.o))
ASSEMBLER_INC_DIR := $(addprefix -I, $(ASSEMBLER_INC_DIR))

.PHONY: asm
asm: $(ASSEMBLER_NAME)

$(ASSEMBLER_NAME): $(ASSEMBLER_OBJ)
	$(CC) $(FLAGS) $(ASSEMBLER_OBJ) $(ASSEMBLER_INC_DIR) -o $(ASSEMBLER_NAME)

$(ASSEMBLER_OBJ): $(ASSEMBLER_OBJ_DIR)/%.o : $(ASSEMBLER_SRC_DIR)/%.c | $(ASSEMBLER_OBJ_DIR)
	$(CC) $(FLAGS) -c $< -o $@ $(ASSEMBLER_INC_DIR)

$(ASSEMBLER_OBJ_DIR):
	@-mkdir $(dir $(ASSEMBLER_OBJ))

.PHONY: assembler_clean
assembler_clean:
	-rm -rf $(ASSEMBLER_OBJ_DIR)

.PHONY: assembler_fclean
assembler_fclean: assembler_clean
	-rm -f $(ASSEMBLER_NAME)
