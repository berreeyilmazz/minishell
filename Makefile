SRCS	= 	./parser/parser_utils.c ./parser/parser_categorize.c \
			./parser/parser_get_tokens_2.c ./parser/parser_get_tokens_main.c \
			./parser/parser_init_and_free.c ./parser/parser_for_quotes.c \
			./parser/parser_for_dollar.c ./parser/parser_dollar_and_quote.c  ./parser/parser_not_clear_but_okey.c\
			./exec/exec_execve.c ./exec/exec_starter.c \
			./executable/executable_redirection.c ./executable/executable_struct.c \
			./builtin/builtin_echo.c ./builtin/builtin_exit.c \
			./builtin/builtin_pwd_cd.c ./builtin/builtin_env.c ./builtin/builtin_unset.c \
			./builtin/builtin_env_2.c ./builtin/builtin_env_plus.c ./builtin/builtin_cd.c\
			./utils/utils.c ./utils/utils_str.c ./utils/signal_settings.c \
			minishell.c

OBJ		= $(SRCS:.c=.o)
NAME	= minishell
NAME_LIBFT = ./libft/libft.a
CC		= gcc
CFLAGS	= -Wall -Werror -Wextra
RD		= -lreadline -lncurses

all	: $(NAME)

$(NAME)	:$(OBJ)
	@make -C ./libft
	@$(CC) $(OBJ) $(NAME_LIBFT) -o $(NAME) $(RD) 

%.o: %.c
	@$(CC) $(CFLAGS) -Imlx -c $< -o $@

clean	:
	@rm -rf $(OBJ) 
	@make fclean -C ./libft

fclean	: clean
	@rm -rf $(NAME) $(NAME_LIBFT)

re	: fclean $(NAME)

.PHONY: all clean fclean re
