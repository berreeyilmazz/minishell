SRCS	= 	./parser/parser_categorize.c ./parser/parser_utils.c \
			./parser/parser_get_tokens_2.c ./parser/parser_get_tokens_main.c \
			./parser/parser_init_and_free.c ./parser/parser_for_quotes.c \
			./parser/parser_for_dollar.c \
			./exec/exec_execve.c ./exec/exec_starter.c \
			./executable/executable_redirection.c ./executable/executable_struct.c \
			./builtin/builtin_echo.c ./builtin/builtin_exit.c \
			./builtin/builtin_pwd_cd.c ./builtin/builtin_env.c \
			./utils/utils.c ./utils/utils_str.c \
			main.c yazdirmafonksiyonları.c 

OBJ		= $(SRCS:.c=.o)
NAME	= minishell
NAME_LIBFT = ./libft/libft/libft.a
CC		= gcc
CFLAGS	= -Wall -Werror -Wextra
RD		= -lreadline -lncurses

all	: $(NAME)

$(NAME)	:$(OBJ)
	@make -C ./libft/libft
	@$(CC) $(CFLAGS) $(OBJ) $(NAME_LIBFT) -o $(NAME) $(RD)

%.o: %.c
	@$(CC) -Wall -Wextra -Werror -Imlx -c $< -o $@

clean	:
	@rm -rf $(OBJ) 
	@make fclean -C ./libft/libft

fclean	: clean
	@rm -rf $(NAME) $(NAME_LIBFT)

re	: fclean $(NAME)

.PHONY: all clean fclean re