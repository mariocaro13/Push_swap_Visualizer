# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mcaro-ro <mcaro-ro@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/13 18:52:13 by mcaro-ro          #+#    #+#              #
#    Updated: 2025/02/13 23:41:21 by mcaro-ro         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Project name
NAME = push_swap_visualizer

# COLORS
GREEN = \033[0;32m
RESET := \033[0m

# INCLUDE directory
INCLUDE_DIR = inc

# SRC DIRS
SRC_DIR = src
COMMANDS_DIR = $(SRC_DIR)/commands

# MINILIBX
MINILIBX_DIR = $(INCLUDE_DIR)/minilibx-linux
MINILIBX = $(MINILIBX_DIR)/libmlx_Linux.a
MINILIBX_FLAGS = -L$(MINILIBX_DIR) -lmlx -lX11 -lXext -lXrandr -lXinerama -lXcursor -lm
# Rule to build the MINILIBX library 
$(MINILIBX):
	@$(MAKE) -C $(MINILIBX_DIR) --silent

#Include dirs
INCLUDE_DIRS = -I$(INCLUDE_DIR) -I$(SRC_DIR) -I$(MINILIBX_DIR)

# Source files and object files
SRC = $(SRC_DIR)/main.c					\
	$(SRC_DIR)/color.c					\
	$(SRC_DIR)/commands.c				\
	$(SRC_DIR)/render.c					\
	$(COMMANDS_DIR)/swap.c				\
	$(COMMANDS_DIR)/push.c				\
	$(COMMANDS_DIR)/rotate.c			\
	$(COMMANDS_DIR)/reverse_rotate.c	\

# Objects files
OBJECTS = $(SRC:.c=.o)

# Compilation settings
CC = cc
CFLAGS = -Wall -Wextra -Werror $(INCLUDE_DIRS) -g3  -fsanitize=address

# Compile source files into object files
%.o: %.c
	@$(CC) -c $< $(CFLAGS) -o $@

# Link object files
$(NAME): $(OBJECTS) $(MINILIBX)
	@$(CC) $(CFLAGS) $(OBJECTS) $(MINILIBX) $(MINILIBX_FLAGS) -o $(NAME)
	@echo "$(GREEN)$(NAME): $(NAME) has been created successfully!$(RESET)"

# Default target to build the project
all: $(NAME)

# Clean up object files
clean:
	@rm -f $(OBJECTS)
	@$(MAKE) -C $(MINILIBX_DIR) clean --silent

# Clean up all generated files
fclean: clean
	@rm -rf $(NAME)

# Rebuild the project
re: fclean all

.DEFAULT_GOAL := all
.PHONY: all clean fclean re
