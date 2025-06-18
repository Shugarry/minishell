# ================================== VARS ==================================== #

NAME = tests
CC = cc
CFLAGS = -Wall -Wextra -Werror -fsanitize=address

SRC_DIR = ../srcs
SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(SRCS:.c=.o)

# Test files
TEST_DIR = .
TEST_SRCS = $(wildcard $(TEST_DIR)/test_*.c)
TEST_OBJS = $(TEST_SRCS:.c=.o)

INCLUDES = -I../libft -I..

HDR = ../minishell.h

# ================================== LIBFT =================================== #

LIBFT_DIR = ../libft
LIBFT = $(LIBFT_DIR)/libft.a

LIB_HDR = $(LIBFT_DIR)/libft.h

# ================================== RULES =================================== #

all: $(NAME)

$(NAME): $(TEST_OBJS) $(OBJS) $(LIBFT)
	@echo "\n==> Linking $(NAME)..."
	@$(CC) $(CFLAGS) $(TEST_OBJS) $(OBJS) -lreadline $(LIBFT) -o $(NAME)

$(TEST_DIR)/%.o: $(TEST_DIR)/%.c $(HDR) $(LIB_HDR) Makefile
	@echo " -> Compiling test: $<"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(SRC_DIR)/%.o: $(SRC_DIR)/%.c $(HDR) $(LIB_HDR) Makefile
	@echo " -> Compiling source: $<"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT): $(LIB_HDR)
	@echo "\n==> Building Libft..."
	@$(MAKE) -C $(LIBFT_DIR)

clean:
	@echo "\n==> Cleaning project..."
	@$(MAKE) -s clean -C $(LIBFT_DIR)
	@rm -f $(OBJS) $(TEST_OBJS)

fclean: clean
	@echo "\n==> Full clean..."
	@$(MAKE) -s fclean -C $(LIBFT_DIR)
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
