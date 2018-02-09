# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hasmith <hasmith@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/01/11 15:20:50 by hasmith           #+#    #+#              #
#    Updated: 2018/02/08 17:02:51 by hasmith          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LIB = lem_in.a

GIT = test

NAME = lem-in

MAIN = main.c

TEST = <argv[1]>

SRC =	srcs/parse.c \
		srcs/make_arrs.c \
		srcs/solve.c \
		srcs/set_links.c

FLAGS = -Wall -Werror -Wextra

all: $(NAME)

$(NAME):
	make all -C libft
	gcc -g -c $(SRC)
	cp libft/libft.a $(LIB) 
	ar rcs $(LIB) *.o
	gcc $(FALGS) -g -o $(NAME) $(LIB) $(MAIN) 
#	gcc $(FALGS) -g -o $(NAME) $(LIB) $(MAIN) minilibx/libmlx.a libft/libft.a -framework OpenGL -framework AppKit

cmain:
	make re
	./lem-in test.txt
#	./resources/filler_vm -f resources/maps/map00 -p1 resources/players/$(PLAYER) -p2 resources/players/abanlin.filler
#	./resources/filler_vm -f resources/maps/map00 -p1 resources/players/$(PLAYER) -p2 resources/players/abanlin.filler > test.txt

clean:
	/bin/rm -f *.o
	make clean -C libft

fclean: clean
	make fclean -C libft
	/bin/rm -f $(NAME)
	/bin/rm -f $(LIB)
#	/bin/rm -rf lem-in.dSYM

re: fclean all

rhe: fclean H

git:
	make fclean
	git add *
	git commit -m '$(GIT)'
	git push
