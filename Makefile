NAME := philo
CC := gcc
CFLAGS := -Wall -Werror -Wextra
CFLAGS += -fsanitize=address
# CFLAGS += -fsanitize=thread -g
SRC_DIR := src/
OBJ_DIR := obj/
SRCS := death.c \
		input_setter.c \
		main.c \
		philos_dining_simulator.c \
		table_setter.c \
		utils.c \
		error_handler.c \
		lonely_philo_simulator.c \
		philo_activities.c \
		printer.c \
		timer.c
OBJS := $(addprefix $(OBJ_DIR),$(SRCS:.c=.o))
HEADER := -I ./include


all:
	$(MAKE) $(NAME) -j

$(OBJ_DIR):
	mkdir -p ./obj

$(NAME): $(OBJ_DIR) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	$(CC) $(CFLAGS) $(HEADER) -c $^ -o $@

clean:
	rm -f $(OBJS)
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
