# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    virtual_machine.mk                                 :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abiri <abiri@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/12/29 18:16:57 by abiri             #+#    #+#              #
#    Updated: 2020/02/12 01:53:44 by abiri            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# EDIT ONLY HERE

VIRTUAL_MACHINE_DIR = ./virtual_machine
VIRTUAL_MACHINE_NAME = corewar
VIRTUAL_MACHINE_SRC_NAMES =	general_tools.c\
							init/arena_init.c\
							init/arg_verification.c\
							init/error_management.c\
							init/op.c\
							init/player_args.c\
							init/player_loading.c\
							instructions/exec_add.c\
							instructions/exec_aff.c\
							instructions/exec_and.c\
							instructions/exec_fork.c\
							instructions/exec_ld.c\
							instructions/exec_ldi.c\
							instructions/exec_lfork.c\
							instructions/exec_live.c\
							instructions/exec_lld.c\
							instructions/exec_lldi.c\
							instructions/exec_or.c\
							instructions/exec_st.c\
							instructions/exec_sti.c\
							instructions/exec_sub.c\
							instructions/exec_xor.c\
							instructions/exec_zjmp.c\
							main.c\
							main_loop.c\
							memory_dump.c\
							parsing/general_parsing_tools.c\
							processes/memory_access.c\
							processes/operation_parser.c\
							processes/process_execution.c\
							processes/processes_init.c\
							visualizer/visualizer_init.c\
							visualizer/visualiser_draw_map.c\
							visualizer/visualiser_draw_menu.c\
							visualizer/visualiser_processes.c

VIRTUAL_MACHINE_INC_NAMES = includes/error_management.h\
							includes/flag_processing.h\
							includes/op.h\
							includes/virtual_machine.h

# AUTOMATIC PART

VIRTUAL_MACHINE_NAME := $(VIRTUAL_MACHINE_DIR)/$(VIRTUAL_MACHINE_NAME)
VIRTUAL_MACHINE_SRC_DIR = $(VIRTUAL_MACHINE_DIR)/sources
VIRTUAL_MACHINE_INC_DIR = $(VIRTUAL_MACHINE_DIR)/includes
VIRTUAL_MACHINE_OBJ_DIR = $(VIRTUAL_MACHINE_DIR)/objects
VIRTUAL_MACHINE_SRC = $(addprefix $(VIRTUAL_MACHINE_SRC_DIR)/, $(VIRTUAL_MACHINE_SRC_NAMES))
VIRTUAL_MACHINE_OBJ = $(addprefix $(VIRTUAL_MACHINE_OBJ_DIR)/, $(VIRTUAL_MACHINE_SRC_NAMES:.c=.o))
VIRTUAL_MACHINE_INC_DIR := $(addprefix -I, $(VIRTUAL_MACHINE_INC_DIR))
VIRTUAL_MACHINE_INC_DIR += -I $(LIBFT_INC) -I $(TTSLIST_INC)
VIRTUAL_MACHINE_OBJ_DIRS = $(sort $(dir $(VIRTUAL_MACHINE_OBJ)))

.PHONY: vm
vm: $(VIRTUAL_MACHINE_NAME)

$(VIRTUAL_MACHINE_NAME): $(VIRTUAL_MACHINE_OBJ) $(LIBFT_NAME) $(TTSLIST_NAME)
	$(CC) $(FLAGS) $(VIRTUAL_MACHINE_OBJ) $(LIBFT_LINK) -lncurses $(TTSLIST_LINK) $(VIRTUAL_MACHINE_INC_DIR) -o $(VIRTUAL_MACHINE_NAME)

$(VIRTUAL_MACHINE_OBJ): $(VIRTUAL_MACHINE_OBJ_DIR)/%.o : $(VIRTUAL_MACHINE_SRC_DIR)/%.c | $(VIRTUAL_MACHINE_OBJ_DIRS)
	$(CC) $(FLAGS) -c $< -o $@ $(VIRTUAL_MACHINE_INC_DIR)

$(VIRTUAL_MACHINE_OBJ_DIRS):
	@-mkdir $(VIRTUAL_MACHINE_OBJ_DIRS)

.PHONY: virtual_machine_clean
virtual_machine_clean:
	-rm -rf $(VIRTUAL_MACHINE_OBJ_DIR)

.PHONY: virtual_machine_fclean
virtual_machine_fclean: virtual_machine_clean
	-rm -f $(VIRTUAL_MACHINE_NAME)
