/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frey-gal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 17:16:01 by frey-gal          #+#    #+#             */
/*   Updated: 2025/01/03 19:19:50 by frey-gal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include <stddef.h>
# include <limits.h>
# include <stdint.h>

char	*cut(char *mem, int x);
void	*ft_calloc(size_t nmemb, size_t size);
char	*free_buddy(char **str, char **str2);
char	*get_next_line(int fd);
char	*butter(char *stash, char *buf);
size_t	length(char *str, char c);
char	*join_free(char *s1, char *s2);
int		find_nl(const char *s);
char	*duplen(const char *s, size_t len);

#endif
