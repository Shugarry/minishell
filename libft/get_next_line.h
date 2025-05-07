/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frey-gal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 17:16:01 by frey-gal          #+#    #+#             */
/*   Updated: 2025/01/03 19:15:04 by frey-gal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include <stddef.h>
# include <limits.h>

char	*cut(char *mem, int x);
char	*free_buddy(char **str, char **str2);
char	*butter(char *stash, char *buf);
char	*get_next_line(int fd);
size_t	length(char *str, char c);
char	*join_free(char *s1, char *s2);
int		find_nl(const char *s);
char	*duplen(const char *s, size_t len);

#endif
