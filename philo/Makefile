CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread -g -fsanitize=thread
# CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address

# VAL = valgrind --leak-check=full --track-origins=yes
HAL = valgrind --tool=helgrind
# DRD = valgrind --tool=drd

SRC = main.c utils.c init.c action.c check.c

OBJ_DIR = obj
OBJ = $(SRC:%.c=$(OBJ_DIR)/%.o)

NAME = philo

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ)
	@echo "\033[32mProgram is ready to execute\033[0m"

$(OBJ_DIR)/%.o: %.c
	@mkdir	-p	$(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJ)
	@rm -rf $(OBJ_DIR)
	@echo "\033[31mAll executables are removed\033[0m"

fclean: clean
	@rm -f $(NAME)

re: fclean all

valgrind: $(NAME)
	$(HAL) ./$(NAME)

.PHONY: all clean fclean re valgrind