NAME = minishell.a

CC = gcc

CFLAGS = -Wall -Werror -Wextra

LIBS = -lreadline

SRC = ./src/minishell.c ./src/builtins/ft_builtins.c ./src/error/ft_error.c ./src/sys_func/ft_sys_func.c

OBJ = $(SRC:.c=.o)

LIBFT_PATH = ./libft/

all: $(NAME)

info: header

define HEADER

        _                                            _ _ _       _                 _       _     _          _ _
       | |                     ___                  | | (_)     ( )               (_)     (_)   | |        | | |
   __ _| | ___   _ _ __ ____  ( _ )   __      _____ | | |_  ___ |/ ___   _ __ ___  _ _ __  _ ___| |__   ___| | |
  / _` | |/ / | | | '__|_  /  / _ \/\ \ \ /\ / / _ \| | | |/ _ \  / __| | '_ ` _ \| | '_ \| / __| '_ \ / _ \ | |
 | (_| |   <| |_| | |   / /  | (_>  <  \ V  V / (_) | | | | (_) | \__ \ | | | | | | | | | | \__ \ | | |  __/ | |
  \__,_|_|\_\\\__,_|_|  /___|  \___/\/   \_/\_/ \___/|_|_|_|\___/  |___/ |_| |_| |_|_|_| |_|_|___/_| |_|\___|_|_|


endef
export HEADER

header:
	@echo "\x1b[35m$$HEADER\x1b[0m"

subsystem : header
	make -C ./libft
	cp ./libft/libft.a libft.a

$(NAME): subsystem
	$(CC) $(CFLAGS) $(LIBS) $(SRC) libft.a -o minishell

clean :
	rm -f $(OBJ)
	rm -f $(LIBFT_PATH)*.o

fclean: clean
	rm -f $(NAME)
	rm -f $(LIBFT_PATH)libft.a
	rm -f libft.a
	rm -f minishell

re: fclean all