NAME = minishell.a

CC = gcc

SRC = ./src/minishell.c ./src/builtins/ft_builtins.c ./src/error/ft_error.c ./src/sys_func/ft_sys_func.c \
		./src/parse/ft_get_env_list.c ./src/helper/ft_helper.c ./src/parse/ft_parse.c ./src/parse/ft_parse2.c \
		./src/helper/ft_helper2.c ./src/parse/ft_parse3.c

OBJ = $(SRC:.c=.o)

ifeq ($(USER), wiliamollio)
		LDFLAGS="-L/usr/local/opt/readline/lib"
		CPPFLAGS="-I/usr/local/opt/readline/include"
else
		LDFLAGS="-L/Users/$(USER)/.brew/opt/readline/lib"
		CPPFLAGS="-I/Users/$(USER)/.brew/opt/readline/include"
endif

CFLAGS = -lreadline $(LDFLAGS) $(CPPFLAGS) -Wall -Wextra -Werror

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
	$(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) $(SRC) libft.a -o minishell

clean :
	rm -f $(OBJ)
	rm -f $(LIBFT_PATH)*.o

fclean: clean
	rm -f $(NAME)
	rm -f $(LIBFT_PATH)libft.a
	rm -f libft.a
	rm -f minishell

re: fclean all
