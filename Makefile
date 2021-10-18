NAME = minishell

CC = gcc

CFLAGS = -Wall -Werror -Wextra

LIBS = -lreadline

SRC = ./src/*.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME):
	$(CC) $(CFLAGS) $(LIBS) $(SRC) -o minishell

fclean:
	rm -rf minishell
	rm -rf $(OBJ)


re: fclean all