# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hasmith <hasmith@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/01/11 15:20:50 by hasmith           #+#    #+#              #
#    Updated: 2018/02/09 14:49:55 by hasmith          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LIB = lem_in.a

GIT = test

NAME = lem-in

MAIN = srcs/main.c

TEST = <argv[1]>

SRC =	srcs/parse.c \
		srcs/make_arrs.c \
		srcs/solve.c \
		srcs/set_links.c

FLAGS = -Wall -Werror -Wextra

all: $(NAME)

$(NAME):
	make all -C libft
	gcc $(FALGS) -g -c $(SRC)
	cp libft/libft.a $(LIB) 
	ar rcs $(LIB) *.o
	gcc $(FALGS) -g -o $(NAME) $(LIB) $(MAIN)
	rm -rf lem-in.dSYM

cmain:
	make re
	./lem-in < test.txt

clean:
	/bin/rm -f *.o
	make clean -C libft

fclean: clean
	make fclean -C libft
	/bin/rm -f $(NAME)
	/bin/rm -f $(LIB)

re: fclean all

rhe: fclean H

git:
	make fclean
	git add *
	git commit -m '$(GIT)'
	git push
