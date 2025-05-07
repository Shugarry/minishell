/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frey-gal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 17:04:20 by frey-gal          #+#    #+#             */
/*   Updated: 2025/01/03 22:53:07 by frey-gal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./get_next_line_bonus.h"

char	*cut(char *mem, int x)
{
	char	*tmp;

	tmp = duplen((mem + x), length(mem, '\0'));
	free(mem);
	if (!tmp)
		return (NULL);
	return (tmp);
}

char	*free_buddy(char **str, char **str2)
{
	if (str && *str)
	{
		free(*str);
		*str = NULL;
	}
	if (str2 && *str2)
	{
		free(*str2);
		*str2 = NULL;
	}
	return (NULL);
}

char	*butter(char *stash, char *buf)
{
	char	*tmp;

	free(buf);
	if (!find_nl(stash))
		tmp = duplen(stash, length(stash, '\0'));
	else
		tmp = duplen(stash, length(stash, '\n') + 1);
	if (!tmp)
		return (NULL);
	return (tmp);
}

int	filler(char **stash, int fd, char *buf)
{
	int	b_read;

	while (!find_nl(stash[fd]))
	{
		b_read = read(fd, buf, BUFFER_SIZE);
		if (b_read < 0)
			return (0);
		buf[b_read] = '\0';
		if (b_read == 0)
			break ;
		stash[fd] = join_free(stash[fd], buf);
		if (!stash[fd])
			return (0);
	}
	return (1);
}

char	*get_next_line(int fd)
{
	static char	*stash[FOPEN_MAX];
	char		*buf;
	char		*next_line;

	if (fd < 0 || fd >= FOPEN_MAX || BUFFER_SIZE <= 0)
		return (NULL);
	buf = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buf)
		return (free_buddy(&stash[fd], &buf));
	if (!filler(stash, fd, buf))
		return (free_buddy(&(stash[fd]), &buf));
	next_line = butter(stash[fd], buf);
	stash[fd] = cut(stash[fd], length(next_line, '\0'));
	if ((!stash[fd] || !next_line) || (!stash[fd] && !buf[0]))
		return (free_buddy(&(stash[fd]), &next_line));
	return (next_line);
}
/*
int	main(int ac, char **av)
{
	if (ac != 2)
		return (0);
	int fd = open(av[1], O_RDWR);
	char *str = get_next_line(fd);
	//int	i = 0;
	while (str)
	{
		//printf("____\n%d iteration\n____\n%s", i++, str);
		printf("%s", str);
		free(str);
		str = get_next_line(fd);
	}
	free(str);
	close(fd);
}*/
