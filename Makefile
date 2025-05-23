##
## EPITECH PROJECT, 2023
## Makefile
## File description:
## Makefile
##

SRC =	src/main.cpp\
		src/phoenix_clicker.cpp\
		src/window.cpp\


OBJ = $(SRC:.cpp=.o)

NAME = phoenix_clicker

CFLAGS = -Wall -Wextra -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

CC = g++

RM = rm -f

all: $(NAME)

$(NAME):$(OBJ)
	$(CC) $(OBJ) -g $(CFLAGS) -o $(NAME)
clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all