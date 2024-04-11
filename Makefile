NAME	= minishell

SRC		= main.c \
		  signal.c \
		  env_queue.c \
		  env_list.c \
		  token_queue.c \
		  token_list.c \
		  check_syntax.c \
		  parse_tokens.c \
		  parser_quote.c \
		  parser_expand.c \
		  utils.c \
		  init_parser_state.c \
		  update_parser_state.c \
		  handle_builtin.c \
		  handle_execution.c \
		  execution.c \
		  handle_redirect.c \
		  heredoc.c \
		  handle_pipe.c \
		  get_next_argv.c \
		  list_to_envp.c \
		  get_pathname.c \
		  get_env.c \
		  list_free.c \
		  echo.c \
		  cd.c \
		  pwd.c \
		  export.c \
		  unset.c \
		  env.c \
		  exit.c \
		  global.c \

OBJ		= $(SRC:.c=.o)

CFLAGS	= -Wall -Wextra -Werror -g

CC		= gcc

$(NAME)	: $(OBJ) minishell.h
	make -C libft
	#$(CC) $(CFLAGS) $(OBJ) -L/Users/$(USER)/.brew/Cellar/readline/8.2.1/lib -lreadline -Llibft -lft -o $(NAME)
	$(CC) $(CFLAGS) $(OBJ) -L/usr/local/opt/readline/lib -lreadline -Llibft -lft -o $(NAME)

%.o		: %.c
	#$(CC) $(CFLAGS) -c $< -I/Users/$(USER)/.brew/Cellar/readline/8.2.1/include -o $@
	$(CC) $(CFLAGS) -c $< -I/usr/local/opt/readline/include -o $@

all		: $(NAME)

clean	:
	$(RM) $(OBJ)

fclean	: clean
	$(RM) $(NAME)

re		: fclean all

r		: all
	@./minishell

.PHONY	: all clean fclean re
