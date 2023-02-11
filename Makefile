NAME	= minishell

SRC		= main.c signal.c

OBJ		= $(SRC:.c=.o)

CFLAGS	= -Wall -Wextra -Werror

CC		= cc

$(NAME)	: $(OBJ) minishell.h
	make -C libft
	$(CC) $(CFLAGS) $(OBJ) -L/Users/$(USER)/.brew/Cellar/readline/8.2.1/lib -lreadline -Llibft -lft -o $(NAME)

%.o		: %.c
	$(CC) $(CFLAGS) -c $< -I/Users/$(USER)/.brew/Cellar/readline/8.2.1/include -o $@

all		: $(NAME)

clean	:
	$(RM) $(OBJ)

fclean	: clean
	$(RM) $(NAME)

re		: fclean all

.PHONY	: all clean fclean re
