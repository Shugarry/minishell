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

static size_t	ft_word_len(char const *s, char c)
{
	size_t	len;

	len = 0;
	while (s && s[len] && s[len] != c)
		len++;
	return (len);
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

static int	ft_fill_words(char const *s, char **split, char c, int size)
{
	int		word;
	size_t	len;
	size_t	i;

	word = 0;
	while (s && *s && word < size)
	{
		while (*s && *s == c)
			s++;
		len = ft_word_len(s, c);
		split[word] = (char *)ft_calloc(len + 1, sizeof(char));
		if (!split[word])
		{
			while (--word >= 0)
				free(split[word]);
			return (0);
		}
		i = 0;
		while (i < len)
			split[word][i++] = *s++;
		split[word++][i] = 0;
		s++;
	}
	split[word] = 0;
	return (1);
}

char	**ft_split(char const *s, char c)
{
	char	**split;
	int		count;

	count = 0;
	if (s && *s && c)
		count = ft_word_count(s, c);
	else if (s && *s)
		count++;
	split = (char **)ft_calloc(count + 1, sizeof(char *));
	if (!split)
		return (0);
	if (!ft_fill_words(s, split, c, count))
	{
		free(split);
		split = NULL;
	}
	return (split);
}
