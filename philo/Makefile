CC = cc -pthread
CFLAGS = -Wall -Wextra -Werror -g -fsanitize=thread
# CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address

VAL = valgrind --leak-check=full --track-origins=yes
# HAL = valgrind --tool=helgrind
# DRD = valgrind --tool=drd

SRC = main.c utils.c init.c action.c

OBJ_DIR = obj
OBJ = $(SRC:%.c=$(OBJ_DIR)/%.o)

NAME = philo

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJ)

$(OBJ_DIR)/%.o: %.c
	@mkdir	-p	$(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

valgrind: $(NAME)
	$(VAL) ./$(NAME)

.PHONY: all clean fclean re