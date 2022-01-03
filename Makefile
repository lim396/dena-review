CC=gcc
CFLAGS=-Wall -Wextra -Werror
NAME=Connect4
SRCS=Connect4.c
OBJS=$(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
