# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    virtual_machine.mk                                 :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abiri <kerneloverseer@pm.me>               +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/12/29 18:16:57 by abiri             #+#    #+#              #
#    Updated: 2019/12/30 16:07:54 by abiri            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# EDIT ONLY HERE

VIRTUAL_MACHINE_DIR = ./virtual_machine
VIRTUAL_MACHINE_NAME = corewar
VIRTUAL_MACHINE_SRC_NAMES = main.c\
							init/arg_verification.c

# AUTOMATIC PART

VIRTUAL_MACHINE_NAME := $(VIRTUAL_MACHINE_DIR)/$(VIRTUAL_MACHINE_NAME)
VIRTUAL_MACHINE_SRC_DIR = $(VIRTUAL_MACHINE_DIR)/sources
VIRTUAL_MACHINE_INC_DIR = $(VIRTUAL_MACHINE_DIR)/includes
VIRTUAL_MACHINE_OBJ_DIR = $(VIRTUAL_MACHINE_DIR)/objects
VIRTUAL_MACHINE_SRC = $(addprefix $(VIRTUAL_MACHINE_SRC_DIR)/, $(VIRTUAL_MACHINE_SRC_NAMES))
VIRTUAL_MACHINE_OBJ = $(addprefix $(VIRTUAL_MACHINE_OBJ_DIR)/, $(VIRTUAL_MACHINE_SRC_NAMES:.c=.o))
VIRTUAL_MACHINE_INC_DIR := $(addprefix -I, $(VIRTUAL_MACHINE_INC_DIR))
VIRTUAL_MACHINE_INC_DIR += -I $(LIBFT_INC)

.PHONY: vm
vm: $(VIRTUAL_MACHINE_NAME)

$(VIRTUAL_MACHINE_NAME): $(VIRTUAL_MACHINE_OBJ) libft
	$(CC) $(FLAGS) $(VIRTUAL_MACHINE_OBJ) $(LIBFT_LINK) $(VIRTUAL_MACHINE_INC_DIR) -o $(VIRTUAL_MACHINE_NAME)

$(VIRTUAL_MACHINE_OBJ): $(VIRTUAL_MACHINE_OBJ_DIR)/%.o : $(VIRTUAL_MACHINE_SRC_DIR)/%.c | $(VIRTUAL_MACHINE_OBJ_DIR)
	echo $(VIRTUAL_MACHINE_INC_DIR)
	$(CC) $(FLAGS) -c $< -o $@ $(VIRTUAL_MACHINE_INC_DIR)

$(VIRTUAL_MACHINE_OBJ_DIR):
	@-mkdir $(dir $(VIRTUAL_MACHINE_OBJ))

.PHONY: virtual_machine_clean
virtual_machine_clean:
	-rm -rf $(VIRTUAL_MACHINE_OBJ_DIR)

.PHONY: virtual_machine_fclean
virtual_machine_fclean: virtual_machine_clean
	-rm -f $(VIRTUAL_MACHINE_NAME)
