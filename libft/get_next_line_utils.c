/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frey-gal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 17:24:06 by frey-gal          #+#    #+#             */
/*   Updated: 2025/01/03 21:44:15 by frey-gal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./get_next_line.h"

size_t	length(char *str, char c)
{
	size_t	i;

	i = 0;
	if (!str || !*str)
	{
		return (0);
	}
	if (c == '\0')
	{
		while (str[i])
			i++;
		return (i);
	}
	else
	{
		while (str[i] != c && str[i])
			i++;
		return (i);
	}
}

char	*join_free(char *s1, char *s2)
{
	char	*tmp;
	size_t	len;
	size_t	i;
	char	*ptr_s1;

	i = 0;
	ptr_s1 = s1;
	if (!s1 && !s2)
		return (NULL);
	len = length(s1, '\0') + length(s2, '\0');
	tmp = (char *)malloc((len + 1) * sizeof(char));
	if (tmp == NULL)
		return (free_buddy(&ptr_s1, NULL));
	if (s1)
		while (*s1)
			tmp[i++] = *s1++;
	if (s2)
		while (*s2)
			tmp[i++] = *s2++;
	tmp[i] = '\0';
	if (ptr_s1)
		free_buddy(&ptr_s1, NULL);
	return (tmp);
}

int	find_nl(const char *s)
{
	int	i;

	i = 0;
	if (!s || !*s)
		return (0);
	while (s[i])
	{
		if (s[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char	*duplen(const char *s, size_t len)
{
	char	*tmp;
	size_t	i;

	if (!s || len == 0)
		return (NULL);
	i = 0;
	tmp = (char *)malloc((len + 1) * sizeof(char));
	if (tmp == NULL)
		return (NULL);
	while (i < len && s[i])
	{
		tmp[i] = s[i];
		i++;
	}
	tmp[i] = '\0';
	return (tmp);
}
