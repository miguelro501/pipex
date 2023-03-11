# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: miguelro <miguelro@students.42lisboa.com>  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/28 17:00:30 by marvin            #+#    #+#              #
#    Updated: 2023/03/11 15:39:45 by miguelro         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

CC = gcc
RM = rm -f
CFLAGS = -Wall -Wextra -Werror -Imlx -g #-fsanitize=address


LIBFT = ./Libft/libft.a
LIBFT_PATH = ./Libft

PRINTF = ./Libft/Printf/libftprintf.a

INCLUDES = -I ./headers/

SRC_PATH = ./sources

OBJ_PATH = ./objects

SRC_NAME = 	main.c\


OBJS = $(addprefix $(OBJ_PATH)/, $(SRC_NAME:.c=.o))

SRC = $(addprefix $(SRC_PATH)/, $(SRC_NAME))

DEFAULT = \033[0;39m
RED = \033[0;91m
GREEN = \033[0;92m
YELLOW = \033[0;93m


all: $(NAME)

$(NAME) : $(OBJS)
	@make -s -C $(LIBFT_PATH)
	@ar rc $(NAME) $(OBJS)
	@ranlib $(NAME)
	@$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) $(LIBFT) $(PRINTF) -o $(NAME)
	@echo "$(GREEN)$(NAME) compiled $(DEFAULT)"

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	@mkdir -p objects
	@$(CC) $(INCLUDES) $(CFLAGS) $(objects) -c $(^) -o $(@)

clean:
	@make clean -s -C $(LIBFT_PATH)
	@rm -rf $(OBJ_PATH)
	@echo "$(YELLOW)$(NAME) files are removed$(DEFAULT)"

fclean:
	@rm -rf objects/
	@make fclean -s -C $(LIBFT_PATH)
	@rm -f $(NAME)
	@echo "$(RED)$(NAME) is deleted$(DEFAULT)"


re: fclean all
