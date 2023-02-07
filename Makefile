NAME	= minishell

SRCS	= main.c signal.c

OBJS	= $(SRCS:.c=.o)

CFLAGS	= -Wall -Wextra -Werror

CC		= cc

$(NAME)	: $(OBJS) minishell.h
	$(CC) $(CFLAGS) $(OBJS) -L/Users/$(USER)/.brew/Cellar/readline/8.2.1/lib -lreadline -o $(NAME)

%.o		: %.c
	$(CC) $(CFLAGS) -c $< -I/Users/$(USER)/.brew/Cellar/readline/8.2.1/include -o $@

all		: $(NAME)

clean	:
	$(RM) $(OBJS)

fclean	: clean
	$(RM) $(NAME)

re		: fclean all

.PHONY	: all clean fclean re
