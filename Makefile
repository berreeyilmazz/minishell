SRCS	= utils.c
OBJ		= $(SRCS:.c=.o)
NAME	= minishell
CC		= gcc -lreadline
CFLAGS	= -Wall -Werror -Wextra

all	: $(NAME)

$(NAME)	:$(OBJ)
			$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

clean	:
	rm -rf $(OBJ)

fclean	:
	rm -rf $(NAME)

re	:
	fclean	$(NAME)

.PHONY: all clean fclean re