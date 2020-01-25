# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    libft_linking.mk                                   :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abiri <kerneloverseer@pm.me>               +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/12/30 14:51:40 by abiri             #+#    #+#              #
#    Updated: 2020/01/23 05:25:49 by abiri            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# LIBFT VARIBLES

LIBFT_DIR = ./libft
LIBFT_NAME := $(LIBFT_DIR)/libft.a
LIBFT_INC := $(LIBFT_DIR)
LIBFT_LINK := -L $(LIBFT_DIR) -lft -L $(LIBFT_DIR)/ft_printf -lftprintf

# TTSLIST VARIBLES

TTSLIST_DIR = ./libraries/ttslist
TTSLIST_NAME := $(TTSLIST_DIR)/libttslist.a
TTSLIST_INC := $(TTSLIST_DIR)/includes
TTSLIST_LINK := -L $(TTSLIST_DIR) -lttslist

# LIBFT RULES

.PHONY: libft
libft: $(LIBFT_NAME)

$(LIBFT_NAME):
	@make -C $(LIBFT_DIR)

.PHONY: libft_clean
libft_clean:
	@make -C $(LIBFT_DIR) clean

.PHONY: libft_fclean
libft_fclean:
	@make -C $(LIBFT_DIR) fclean

# TTSLIST RULES

.PHONY: ttslist
ttslist: $(TTSLIST_NAME)

$(TTSLIST_NAME):
	@make -C $(TTSLIST_DIR)

.PHONY: ttslist_clean
ttslist_clean:
	@make -C $(TTSLIST_DIR) clean

.PHONY: ttslist_fclean
ttslist_fclean:
	@make -C $(TTSLIST_DIR) fclean
