# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: miggarc2 <miggarc2@student.42barcelona.co  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/18 19:51:13 by miggarc2          #+#    #+#              #
#    Updated: 2025/06/05 23:07:05 by frey-gal         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC= cc
CFLAGS= -Wall -Wextra -Werror -I .
RM= rm -f
NAME= libft.a
INC= libft.h
SRC= ft_atoi.c ft_strlcat.c  ft_bzero.c ft_strlcpy.c  ft_tolower.c ft_memchr.c \
	 ft_strlen.c   ft_toupper.c ft_isalnum.c ft_memcmp.c ft_isalpha.c \
	 ft_memcpy.c ft_strchr.c ft_strncmp.c ft_isascii.c \
	 ft_memmove.c ft_strnstr.c ft_isdigit.c ft_memset.c ft_strrchr.c \
	 ft_isprint.c ft_calloc.c ft_putendl_fd.c ft_strdup.c ft_strtrim.c \
	 ft_itoa.c ft_putnbr_fd.c ft_striteri.c ft_substr.c ft_putstr_fd.c \
	 ft_strjoin.c ft_putchar_fd.c ft_split.c ft_strmapi.c \
	 ft_lstadd_back_bonus.c ft_lstclear_bonus.c ft_lstiter_bonus.c \
	 ft_lstmap_bonus.c ft_lstsize_bonus.c ft_lstadd_front_bonus.c \
	 ft_lstdelone_bonus.c ft_lstlast_bonus.c ft_lstnew_bonus.c \
	 ft_printf_bonus.c ft_printf_utils_bonus.c ft_printf_utils2_bonus.c \
	 get_next_line_bonus.c

OBJ= ${SRC:.c=.o}

%.o: %.c $(INC) Makefile
	@$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJ)
	@ar -rcs $(NAME) $(OBJ)

clean:
	@$(RM) $(wildcard *.o)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
