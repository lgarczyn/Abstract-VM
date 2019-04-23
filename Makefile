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

SRC_PATH = ./src/
OBJ_PATH  = ./obj/
INCLUDES = -I $(SRC_PATH) -I $(OBJ_PATH)

FLAGS = -Wall -Wextra -Werror -std=c++1z -O2 $(INCLUDES)

SRC_NAMES = main.cpp \
			VM.cpp \
			Exceptions/VMException.cpp \
			Operands/Operand.cpp \
			Operands/OperandFactory.cpp \
			Operations/Operation.cpp \
			Parsing/Lexer.cpp \
			Parsing/Parser.cpp \

HEADER_NAMES = \
			Libs/Argument_helper.hpp \
			Libs/SafeInt.hpp \
			Exceptions/VMException.hpp \
			Operands/IOperand.hpp \
			Operands/Operand.hpp \
			Operands/OperandFactory.hpp \
			Operations/Operation.hpp \
			Parsing/Lexer.hpp \
			Parsing/Parser.hpp \
			VM.hpp

SRCS = $(addprefix $(SRC_PATH), $(SRC_NAMES))
HEADERS = $(addprefix $(SRC_PATH), $(HEADER_NAMES))

OBJ =  $(addprefix $(OBJ_PATH), $(SRC_NAMES:.cpp=.o))

all:
	$(MAKE) -j8 $(NAME)

$(NAME): $(OBJ)
	g++ $(FLAGS) $(OBJ) -o $(NAME)

$(OBJ_PATH)%.o: $(SRC_PATH)%.cpp $(HEADERS)
	mkdir -p `dirname $@`
	g++ -c $(FLAGS) $< -o $@

clean:
	/bin/rm -rf $(OBJ_PATH)

fclean: clean
	/bin/rm -rf $(NAME)

re:
	$(MAKE) fclean
	$(MAKE) all

.PHONY: all, clean, fclean, re
