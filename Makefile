# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: imunaev- <imunaev-@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/11 07:28:17 by imunaev-          #+#    #+#              #
#    Updated: 2024/12/11 08:08:46 by imunaev-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# SETTINGS
NAME        = pipex
CC          = cc
CFLAGS      = -Wall -Wextra -Werror
LIBFT_DIR   = ./libft
LIBFT       = $(LIBFT_DIR)/libft.a
INCLUDES    = -I./ -I$(LIBFT_DIR)

# SOURCES
SRCS        = pipex.c utils.c
OBJS        = $(SRCS:.c=.o)

# RULES
all: $(NAME)

$(NAME): $(OBJS)
	@make -C $(LIBFT_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) $(LIBFT) -o $(NAME)

%.o: %.c pipex.h
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJS)
	make clean -C $(LIBFT_DIR)

fclean: clean
	rm -f $(NAME)
	make fclean -C $(LIBFT_DIR)

re: fclean all

.PHONY: all clean fclean re
