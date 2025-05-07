# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: frey-gal <frey-gal@student.42barcelona.co  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/20 01:47:03 by frey-gal          #+#    #+#              #
#    Updated: 2025/04/20 02:32:17 by frey-gal         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ================================== VARS ==================================== #

NAME	= libft.a
CC		= cc
CFLAGS	= -Wall -Wextra -Werror

SRC =	\
ft_atoi.c \
ft_bzero.c \
ft_calloc.c \
ft_isalnum.c \
ft_isalpha.c \
ft_isascii.c \
ft_isdigit.c \
ft_isprint.c \
ft_itoa.c \
ft_memchr.c \
ft_memcmp.c \
ft_memcpy.c \
ft_memmove.c \
ft_memset.c \
ft_putchar_fd.c \
ft_putendl_fd.c \
ft_putnbr_fd.c \
ft_putstr_fd.c \
ft_split.c \
ft_strchr.c \
ft_strdup.c \
ft_striteri.c \
ft_strjoin.c \
ft_strlcat.c \
ft_strlcpy.c \
ft_strlen.c \
ft_strmapi.c \
ft_strncmp.c \
ft_strnstr.c \
ft_strrchr.c \
ft_strtrim.c \
ft_substr.c \
ft_tolower.c \
ft_toupper.c \
ft_printf.c \
print_base.c \
print_uns.c \
print_ptr.c \
print_str.c \
print_char.c \
get_next_line.c \
get_next_line_bonus.c \
get_next_line_utils_bonus.c \
get_next_line_utils.c \
ft_lstnew_bonus.c \
ft_lstadd_front_bonus.c \
ft_lstsize_bonus.c \
ft_lstlast_bonus.c \
ft_lstadd_back_bonus.c \
ft_lstdelone_bonus.c \
ft_lstclear_bonus.c \
ft_lstiter_bonus.c \
ft_lstmap_bonus.c \

OBJ		= $(SRC:.c=.o)

HEADERS	= \
libft.h \
get_next_line.h \
get_next_line_bonus.h \
ft_printf.h

# ================================== RULES =================================== #

all: $(NAME)

$(NAME): $(OBJ) Makefile
	@echo "\n -> Making Libft library..."
	@ar rcs $@ $(OBJ)

%.o: %.c $(HEADERS) Makefile
	@echo "    * libft: Compiling $<"
	@$(CC) $(CFLAGS) -I. -c $< -o $@

clean:
	@echo "\n -> Cleaning libft..."
	@rm -f $(OBJ)

fclean: clean
	@echo "\n -> Full libft clean..."
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
