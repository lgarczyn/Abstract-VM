# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lgarczyn <lgarczyn@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/01/22 17:11:22 by lgarczyn          #+#    #+#              #
#    Updated: 2015/06/24 12:57:18 by lgarczyn         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = abstract-vm

SRCS_PATH = ./src/
OBJ_PATH  = ./obj/

FLAGS = -Wall -Werror -Wextra -std=c++14

SRCS_NAME = main.cpp \
			Operations/Operand.cpp \
			Operations/OperandFactory.cpp \
			Operations/Operation.cpp \
			Parsing/Lexer.cpp \

SRCS = $(addprefix $(SRCS_PATH), $(SRCS_NAME))
OBJ = $(addprefix $(OBJ_PATH), $(SRCS_NAME:.cpp=.o))

all: $(NAME)

$(NAME): $(OBJ)
	@g++ $(FLAGS) $(OBJ) -o $(NAME)

$(OBJ_PATH)%.o: $(SRCS_PATH)%.cpp
	@mkdir -p `dirname $@`
	@g++ -c $(FLAGS) $< -o $@

clean:
	@/bin/rm -rf $(OBJ_PATH)

fclean: clean
	@/bin/rm -rf $(NAME)

re: fclean all

.PHONY: all, clean, fclean, re
