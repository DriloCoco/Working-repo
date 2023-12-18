# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nicsanch <nico_sp_92@hotmail.com>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/01 20:58:10 by nicsanch          #+#    #+#              #
#    Updated: 2023/10/02 12:51:38 by nicsanch         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

TARGET = $(BIN_DIR)/philo

FILES = test.c				\
		main.c				\

BIN_DIR = ./bin

OBJS = $(addprefix $(OBJ_DIR)/,$(FILES:%.c=%.o))

INC_DIR = ./inc
OBJ_DIR = ./obj
SRC_DIR = ./src

INCLUDES = -I$(INC_DIR)
CFLAGS =   -pthread -fsanitize=thread -g
# -Wall -Wextra -Werror

$(TARGET): $(OBJS)
	mkdir -p $(BIN_DIR) 
	gcc $(CFLAGS) $(INCLUDES) $^ -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(OBJ_DIR)
	gcc $(CFLAGS) $(INCLUDES) -c $< -o $@

.PHONY: all clean fclean re run

all: $(TARGET)

clean:
	@if [ -d $(OBJ_DIR) ]; then \
		rm -r $(OBJ_DIR); \
	fi

fclean: clean
	@if [ -d $(BIN_DIR) ]; then \
		rm -r $(BIN_DIR); \
	fi

run:
	./bin/philo 5 800 200 200 7

re: fclean all
