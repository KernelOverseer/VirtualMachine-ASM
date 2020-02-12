# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    assembler.mk                                       :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aelouarg <aelouarg@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/12/29 17:57:31 by abiri             #+#    #+#              #
#    Updated: 2020/02/12 01:53:44 by abiri            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# EDIT ONLY HERE

ASSEMBLER_DIR 		=	./assembler
ASSEMBLER_NAME 		=	asm
ASSEMBLER_SRC_NAMES =	allocations.c bytecode_file_generator.c bytecode_from_assembly.c \
						bytecode_from_header.c check_file.c error.c free_structures.c \
						get_size_champ.c main.c op.c read_arguments.c read_commands.c \
						read_file.c read_instructions.c read_labels.c size_champ.c store_commands.c \
						tools.c type_args.c white_spaces.c write_types.c get_line.c multi_line_tools.c

# AUTOMATIC PART

ASSEMBLER_NAME := $(ASSEMBLER_DIR)/$(ASSEMBLER_NAME)
ASSEMBLER_SRC_DIR = $(ASSEMBLER_DIR)/sources
ASSEMBLER_INC_DIR = $(ASSEMBLER_DIR)/includes
ASSEMBLER_OBJ_DIR = $(ASSEMBLER_DIR)/objects
ASSEMBLER_SRC = $(addprefix $(ASSEMBLER_SRC_DIR)/, $(ASSEMBLER_SRC_NAMES))
ASSEMBLER_OBJ = $(addprefix $(ASSEMBLER_OBJ_DIR)/, $(ASSEMBLER_SRC_NAMES:.c=.o))
ASSEMBLER_INC_DIR := $(addprefix -I, $(ASSEMBLER_INC_DIR))
ASSEMBLER_INC_DIR += -I $(LIBFT_INC)
ASSEMBLER_OBJ_DIRS = $(sort $(dir $(ASSEMBLER_OBJ)))

.PHONY: asm
asm: $(ASSEMBLER_NAME)

$(ASSEMBLER_NAME): $(ASSEMBLER_OBJ) $(LIBFT_NAME)
	$(CC) $(FLAGS) $(ASSEMBLER_OBJ) $(LIBFT_LINK) $(ASSEMBLER_INC_DIR) -o $(ASSEMBLER_NAME)

$(ASSEMBLER_OBJ): $(ASSEMBLER_OBJ_DIR)/%.o : $(ASSEMBLER_SRC_DIR)/%.c | $(ASSEMBLER_OBJ_DIRS)
	$(CC) $(FLAGS) -c $< -o $@ $(ASSEMBLER_INC_DIR)

$(ASSEMBLER_OBJ_DIRS):
	@-mkdir $(ASSEMBLER_OBJ_DIRS)

.PHONY: assembler_clean
assembler_clean:
	-rm -rf $(ASSEMBLER_OBJ_DIR)

.PHONY: assembler_fclean
assembler_fclean: assembler_clean
	-rm -f $(ASSEMBLER_NAME)
