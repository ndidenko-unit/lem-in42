#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ndidenko <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/08/03 13:27:12 by ndidenko          #+#    #+#              #
#    Updated: 2018/08/03 13:27:14 by ndidenko         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = lem-in

FILE_C =  main.c room.c link.c bfs.c create_rd.c let_my_people_go.c valid.c

FILE_O = $(FILE_C:.c=.o)

GCC = gcc

FLAG = -Wall -Wextra -Werror

LIB_INC = -I libft/

LIBNAME = ./libft/libft.a

all: $(NAME)

$(LIBNAME): ./libft/libft.h
	@make -C ./libft

$(NAME): $(LIBNAME) $(FILE_O)
	@$(GCC) $(FILE_O) ./libft/libft.a -o $(NAME)
	@echo "-----====== COMPLETE ======-----"

%.o: %.c
	@$(GCC) $(FLAG) -c $< $(LIB_INC)

clean:
	@make -C ./libft clean
	@rm -f $(FILE_O)
	@echo "---=== CLEANING DONE RIGHT ===---"

fclean: clean
	@make -C ./libft fclean
	@rm -f $(NAME)

re: fclean all
	@make -C ./libft fclean