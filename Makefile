NAME	= minishell

SRCS	= main.c

OBJS	= $(SRCS:.c=.o)

CFLAGS	= -Wall -Wextra -Werror -g

CC		= gcc

$(NAME)	: $(OBJS) minishell.h
	$(CC) $(CFLAGS) $(OBJS) -lreadline -o $(NAME)

%.o		: %.c
	$(CC) $(CFLAGS) -c $< -o $@

all		: $(NAME)

clean	:
	$(RM) $(OBJS)

fclean	: clean
	$(RM) $(NAME)

re		: fclean all

.PHONY	: all clean fclean re
