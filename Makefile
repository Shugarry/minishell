# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: frey-gal <frey-gal@student.42barcelona.co  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/20 02:23:03 by frey-gal          #+#    #+#              #
#    Updated: 2025/07/10 21:27:18 by frey-gal         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ================================== VARS ==================================== #

NAME		= minishell
CC			= cc
CFLAGS		= -Wall -Wextra -Werror -g #-fsanitize=address
LFLAGS		= -lreadline
RM			= rm -f

# ================================== SOURCES ================================== #

SRC			= $(addprefix srcs/minishell_, builtins_chdir.c builtins_extra.c \
			  builtins_vars.c env_helpers.c env_init.c exec.c expansion.c \
			  expansion_helpers.c init.c memory.c signals.c tokens.c \
			  utils.c)

OBJ			= $(SRC:.c=.o)

INC 		= -Ilibft -I.

HDR			= minishell.h

# ================================== LIBFT =================================== #

LIBFT_DIR	= libft
LIBFT		= $(LIBFT_DIR)/libft.a

LIB_HDR		= $(LIBFT_DIR)/libft.h

LIB_SRC		= $(addprefix libft/ft_, atoi.c bzero.c calloc.c isalnum.c isalpha.c \
				isascii.c isdigit.c isprint.c itoa.c lstadd_back_bonus.c \
				lstadd_front_bonus.c lstclear_bonus.c lstdelone_bonus.c \
				lstiter_bonus.c lstlast_bonus.c lstmap_bonus.c lstnew_bonus.c \
				lstsize_bonus.c memchr.c memcmp.c memcpy.c memmove.c memset.c \
				printf_bonus.c printf_utils2_bonus.c printf_utils_bonus.c \
				putchar_fd.c putendl_fd.c putnbr_fd.c putstr_fd.c split.c strchr.c \
				strdup.c striteri.c strjoin.c strlcat.c strlcpy.c strlen.c \
				strmapi.c strncmp.c strnstr.c strrchr.c strtrim.c substr.c \
				tolower.c toupper.c) $(addprefix libft/, get_next_line_bonus.c)

LIB_DEP = $(LIB_SRC) $(LIB_HDR) libft/Makefile 

# ================================== RULES =================================== #

all: $(NAME)

# Linking
$(NAME): $(OBJ) $(LIBFT)
	@echo "\n==> Linking $(NAME)..."
	@$(CC) $(CFLAGS) $(OBJ) $(LFLAGS) $(LIBFT) -o $(NAME)

# Compiling
%.o: %.c $(HDR) $(LIB_HDR) Makefile
	@echo " -> Compiling $<"
	@$(CC) $(CFLAGS) $(INC) -c $< -o $@

# Building Libft
$(LIBFT): $(LIB_DEP)
	@echo "\n==> Building Libft..."
	@$(MAKE) -C $(LIBFT_DIR)

# Cleaning
clean:
	@echo "\n==> Cleaning project..."
	@$(MAKE) -s clean -C $(LIBFT_DIR)
	@$(RM) $(OBJ)

fclean: clean
	@echo "\n==> Full clean..."
	@$(MAKE) -s fclean -C $(LIBFT_DIR)
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus
