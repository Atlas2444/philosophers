NAME = philosophers

SRCS = philo/main.c \
    philo/parsing.c \
    philo/init.c \
    philo/thread.c \
    philo/philosopher.c \
    philo/philosopher_utils.c \
    philo/monitor.c \
    philo/utils.c

OBJS = $(SRCS:.c=.o)

CC = gcc
CFLAGS = -Wall -Wextra -Werror -pthread -g
INC = -I.

RM = rm -f

all: $(NAME)

$(NAME): $(OBJS)
	@echo "Linking $(NAME)..."
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "Built $(NAME)"

%.o: %.c
	@echo "Compiling $<..."
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

clean:
	@echo "Removing object files..."
	$(RM) $(OBJS)

fclean: clean
	@echo "Removing executable..."
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re