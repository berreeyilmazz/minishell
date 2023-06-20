SRCS	= utils.c
OBJ		= $(SRCS:.c=.o)
NAME	= minishell
CC		= gcc
CFLAGS	= -Wall -Werror -Wextra
RD		= -lreadline -lncurses

all	: $(NAME)

$(NAME)	:$(OBJ)
			$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(RD)

clean	:
	rm -rf $(OBJ) $(NAME)

fclean	:
	rm -rf $(NAME)

re	: fclean $(NAME)

.PHONY: all clean fclean re