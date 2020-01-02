# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    virtual_machine.mk                                 :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abiri <kerneloverseer@pm.me>               +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/12/29 18:16:57 by abiri             #+#    #+#              #
#    Updated: 2020/01/02 13:31:21 by abiri            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# EDIT ONLY HERE

VIRTUAL_MACHINE_DIR = ./virtual_machine
VIRTUAL_MACHINE_NAME = corewar
VIRTUAL_MACHINE_SRC_NAMES =	general_tools.c\
							init/arg_verification.c\
							init/error_management.c\
							init/op.c\
							init/player_args.c\
							init/player_loading.c\
							init/vm_process_init.c\
							main.c\
							parsing/general_parsing_tools.c

# AUTOMATIC PART

VIRTUAL_MACHINE_NAME := $(VIRTUAL_MACHINE_DIR)/$(VIRTUAL_MACHINE_NAME)
VIRTUAL_MACHINE_SRC_DIR = $(VIRTUAL_MACHINE_DIR)/sources
VIRTUAL_MACHINE_INC_DIR = $(VIRTUAL_MACHINE_DIR)/includes
VIRTUAL_MACHINE_OBJ_DIR = $(VIRTUAL_MACHINE_DIR)/objects
VIRTUAL_MACHINE_SRC = $(addprefix $(VIRTUAL_MACHINE_SRC_DIR)/, $(VIRTUAL_MACHINE_SRC_NAMES))
VIRTUAL_MACHINE_OBJ = $(addprefix $(VIRTUAL_MACHINE_OBJ_DIR)/, $(VIRTUAL_MACHINE_SRC_NAMES:.c=.o))
VIRTUAL_MACHINE_INC_DIR := $(addprefix -I, $(VIRTUAL_MACHINE_INC_DIR))
VIRTUAL_MACHINE_INC_DIR += -I $(LIBFT_INC) -I $(TTSLIST_INC)

.PHONY: vm
vm: $(VIRTUAL_MACHINE_NAME)

$(VIRTUAL_MACHINE_NAME): $(VIRTUAL_MACHINE_OBJ) libft ttslist
	$(CC) $(FLAGS) $(VIRTUAL_MACHINE_OBJ) $(LIBFT_LINK) $(TTSLIST_LINK) $(VIRTUAL_MACHINE_INC_DIR) -o $(VIRTUAL_MACHINE_NAME)

$(VIRTUAL_MACHINE_OBJ): $(VIRTUAL_MACHINE_OBJ_DIR)/%.o : $(VIRTUAL_MACHINE_SRC_DIR)/%.c | $(VIRTUAL_MACHINE_OBJ_DIR)
	$(CC) $(FLAGS) -c $< -o $@ $(VIRTUAL_MACHINE_INC_DIR)

$(VIRTUAL_MACHINE_OBJ_DIR):
	@-mkdir $(dir $(VIRTUAL_MACHINE_OBJ))

.PHONY: virtual_machine_clean
virtual_machine_clean:
	-rm -rf $(VIRTUAL_MACHINE_OBJ_DIR)

.PHONY: virtual_machine_fclean
virtual_machine_fclean: virtual_machine_clean
	-rm -f $(VIRTUAL_MACHINE_NAME)
