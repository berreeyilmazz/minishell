SRCS	= 	parser_categorize.c	parser_utils.c	parser_get_tokens_2.c \
				parser_get_tokens_main.c parser_init_and_free.c \
				parser_for_quotes.c main.c \
				builtin_echo.c	builtin_exit.c builtin_pwd_cd.c \
utils.c utils_str.c exec_execve.c exec_starter.c executable_redirection.c \
executable_struct.c parser_for_dollar.c builtin_env.c

OBJ		= $(SRCS:.c=.o)
NAME	= minishell
NAME_LIBFT = ./libft/libft.a
CC		= gcc
CFLAGS	= -Wall -Werror -Wextra
RD		= -lreadline -lncurses

all	: $(NAME)

$(NAME)	:$(OBJ)
	@make -C ./libft
	@$(CC) $(CFLAGS) $(OBJ) $(NAME_LIBFT) -o $(NAME) $(RD)

%.o: %.c
	@$(CC) -Wall -Wextra -Werror -Imlx -c $< -o $@

clean	:
	@rm -rf $(OBJ) 
	@make fclean -C ./libft

fclean	: clean
	@rm -rf $(NAME) $(NAME_LIBFT)

re	: fclean $(NAME)

.PHONY: all clean fclean re