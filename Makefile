NAME := philo
CC := cc
CFLAGS := -Wall -Werror -Wextra

SRC_DIR := src/
OBJ_DIR := obj/
SRCS :=
OBJS := $(addprefix $(OBJ_DIR),$(SRCS:.c=.o))
HEADER := -I ./include

all:
	$(MAKE) $(NAME) -j

$(OBJ_DIR):
	mkdir -p ./obj

$(NAME): $(OBJ_DIR) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@$(CC) $(CFLAGS) $(HEADER) -c $^ -o $@

clean:
	rm -f $(OBJS)
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
