# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: frey-gal <frey-gal@student.42barcelona.co  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/20 02:23:03 by frey-gal          #+#    #+#              #
#    Updated: 2025/05/14 23:51:38 by miggarc2         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ================================== VARS ==================================== #

NAME		= minishell
CC			= cc
CFLAGS		= -Wall -Wextra -Werror -g #-fsanitize=address
LFLAGS		= -lreadline

SRC			= $(addprefix srcs/minishell_, main.c exec.c input.c signals.c \
			utils.c)

OBJ			= $(SRC:.c=.o)

INC 		= -Ilibft -I.

HDR			= minishell.h

# ================================== LIBFT =================================== #

LIBFT_DIR	= libft
LIBFT		= $(LIBFT_DIR)/libft.a

LIB_HDR		= libft/libft.h

LIB_SRC		= \
libft/ft_atoi.c \
libft/ft_bzero.c \
libft/ft_calloc.c \
libft/ft_isalnum.c \
libft/ft_isalpha.c \
libft/ft_isascii.c \
libft/ft_isdigit.c \
libft/ft_isprint.c \
libft/ft_itoa.c \
libft/ft_lstadd_back_bonus.c \
libft/ft_lstadd_front_bonus.c \
libft/ft_lstclear_bonus.c \
libft/ft_lstdelone_bonus.c \
libft/ft_lstiter_bonus.c \
libft/ft_lstlast_bonus.c \
libft/ft_lstmap_bonus.c \
libft/ft_lstnew_bonus.c \
libft/ft_lstsize_bonus.c \
libft/ft_memchr.c \
libft/ft_memcmp.c \
libft/ft_memcpy.c \
libft/ft_memmove.c \
libft/ft_memset.c \
libft/ft_printf_bonus.c \
libft/ft_printf_utils2_bonus.c \
libft/ft_printf_utils_bonus.c \
libft/ft_putchar_fd.c \
libft/ft_putendl_fd.c \
libft/ft_putnbr_fd.c \
libft/ft_putstr_fd.c \
libft/ft_split.c \
libft/ft_strchr.c \
libft/ft_strdup.c \
libft/ft_striteri.c \
libft/ft_strjoin.c \
libft/ft_strlcat.c \
libft/ft_strlcpy.c \
libft/ft_strlen.c \
libft/ft_strmapi.c \
libft/ft_strncmp.c \
libft/ft_strnstr.c \
libft/ft_strrchr.c \
libft/ft_strtrim.c \
libft/ft_substr.c \
libft/ft_tolower.c \
libft/ft_toupper.c \
libft/get_next_line_bonus.c 

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

$(LIBFT): $(LIB_DEP)
	@echo "\n==> Building Libft..."
	@$(MAKE) -C $(LIBFT_DIR)

# Cleaning
clean:
	@echo "\n==> Cleaning project..."
	@$(MAKE) -s clean -C $(LIBFT_DIR)
	@rm -f $(OBJ)

fclean: clean
	@echo "\n==> Full clean..."
	@$(MAKE) -s fclean -C $(LIBFT_DIR)
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus
