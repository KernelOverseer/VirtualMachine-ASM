# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    libft_linking.mk                                   :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abiri <kerneloverseer@pm.me>               +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/12/30 14:51:40 by abiri             #+#    #+#              #
#    Updated: 2019/12/30 14:58:26 by abiri            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LIBFT_DIR = ./libft
LIBFT_NAME := $(LIBFT_DIR)/libft.a

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
