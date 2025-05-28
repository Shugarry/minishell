/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miggarc2 <miggarc2@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 17:54:28 by miggarc2          #+#    #+#             */
/*   Updated: 2025/02/26 23:27:37 by miggarc2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_word_mem(char const *s, char c, char **split, int word)
{
	size_t	len;

	len = 0;
	while (s && s[len] && s[len] != c)
		len++;
	split[word] = (char *)ft_calloc(len + 1, sizeof(char));
	if (!split[word])
	{
		while (--word >= 0)
			free(split[word]);
		return (0);
	}
	return (len);
}

static int	ft_fill_words(char const *s, char **split, char c, int size)
{
	int		word;
	size_t	len;
	size_t	i;
	size_t	j;

	word = 0;
	j = 0;
	while (word < size)
	{
		while (s[j] && s[j] == c)
			j++;
		len = ft_word_mem(&s[j], c, split, word);
		if (len == 0)
			return (1);
		i = 0;
		while (i < len)
			split[word][i++] = s[j++];
		split[word++][i] = 0;
		j++;
	}
	return (0);
}

static int	ft_word_count(char const *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s && s[i])
	{
		if (s[i] != c)
		{
			count++;
			while (s[i] && s[i] != c)
				i++;
		}
		while (s[i] == c)
			i++;
	}
	return (count);
}

char	**ft_split(char const *s, char c)
{
	char	**split;
	int		size;

	size = 0;
	if (s && *s && c)
		size = ft_word_count(s, c);
	else if (s && *s)
		size++;
	split = (char **)ft_calloc(size + 1, sizeof(char *));
	if (!split)
		return (NULL);
	split[size] = NULL;
	if (ft_fill_words(s, split, c, size))
	{
		free(split);
		split = NULL;
	}
	return (split);
}
