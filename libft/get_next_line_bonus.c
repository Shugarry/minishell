/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miggarc2 <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 22:16:17 by miggarc2          #+#    #+#             */
/*   Updated: 2025/02/25 23:02:30 by miggarc2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_check_line(char *line)
{
	int	len;

	len = 0;
	if (!line || !line[len])
		return (0);
	while (line[len] && line[len] != '\n')
		len++;
	return (len);
}

static _Bool	ft_read_file(char **line, int fd, int *len, ssize_t *rd)
{
	char	*tmp;
	char	*del;

	tmp = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!tmp)
		return (0);
	*rd = read(fd, tmp, BUFFER_SIZE);
	while (*rd > 0)
	{
		tmp[*rd] = '\0';
		del = *line;
		*line = ft_strjoin(*line, tmp);
		free(del);
		del = NULL;
		if (!(*line))
			return (0);
		*len += ft_check_line(&(*line)[*len]);
		if ((*line)[*len] == '\n')
			break ;
		*rd = read(fd, tmp, BUFFER_SIZE);
	}
	free(tmp);
	tmp = NULL;
	return (1);
}

static _Bool	ft_trim_line(char **buff, char **line, int len)
{
	char	*del;

	if (*line && (*line)[len])
	{
		*buff = ft_strdup(&(*line)[len + 1]);
		if (!(*buff))
			return (0);
		(*line)[len + 1] = '\0';
	}
	del = *line;
	*line = ft_strdup(*line);
	if (del)
		free(del);
	del = NULL;
	if (!(*line))
		return (0);
	else if (!(**line))
	{
		free(*line);
		return (0);
	}
	return (1);
}

char	*get_next_line(int fd)
{
	static char	*buff[1024];
	char		*line;
	int			len;
	ssize_t		rd;

	rd = 0;
	if (BUFFER_SIZE < 1 || fd < 0 || fd > 1024)
		return (NULL);
	line = buff[fd];
	buff[fd] = NULL;
	len = ft_check_line(line);
	if (!line || line[len] != '\n')
		if (!ft_read_file(&line, fd, &len, &rd))
			return (NULL);
	if (rd < 0)
	{
		free(line);
		line = NULL;
	}
	else if (!ft_trim_line(&buff[fd], &line, len))
		return (NULL);
	return (line);
}
