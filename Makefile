CC = cc -g -pthread
CFLAGS = -Wall -Wextra -Werror -g  -fsanitize=thread

# -fsanitize=address

VAL = valgrind --leak-check=full --track-origin=yes --tool=helgrind --tool=drd

SRC = main.c utils.c init.c action.c

OBJ = $(SRC:.c=.o)

NAME = philo

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJ)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all