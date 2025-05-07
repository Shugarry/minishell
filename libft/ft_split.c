/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frey-gal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 20:09:36 by frey-gal          #+#    #+#             */
/*   Updated: 2024/10/16 16:55:07 by frey-gal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

size_t	array_size(const char *s, char c)
{
	size_t	i;
	size_t	ctr;

	i = 0;
	ctr = 0;
	while (s[i])
	{
		while (s[i] == c && s[i])
			i++;
		if (s[i] && s[i] != c)
		{
			ctr++;
			while (s[i] && s[i] != c)
				i++;
		}
	}
	return (ctr);
}

size_t	string_size(const char *s, char c)
{
	size_t	ctr;

	ctr = 0;
	while (s[ctr] && s[ctr] != c)
		ctr++;
	return (ctr);
}

int	error_free(char **ptr)
{
	int	i;

	i = 0;
	if (!ptr)
		return (0);
	while (ptr[i])
	{
		free(ptr[i]);
		ptr[i] = NULL;
		i++;
	}
	free(ptr);
	return (0);
}

int	fill_arr(const char *s, char **arr, char c, size_t arr_size)
{
	size_t	i;
	size_t	j;
	size_t	str_size;

	i = 0;
	while (i < arr_size)
	{
		while (*s == c && *s)
			s++;
		str_size = string_size(s, c);
		arr[i] = (char *)malloc((str_size + 1) * sizeof(char));
		if (!arr[i])
			return (error_free(arr));
		j = 0;
		while (j < str_size)
			arr[i][j++] = *s++;
		arr[i][j] = '\0';
		i++;
	}
	arr[arr_size] = NULL;
	return (1);
}

char	**ft_split(const char *s, char c)
{
	char	**arr;
	size_t	arr_size;

	if (!s)
		return (NULL);
	arr_size = array_size(s, c);
	arr = (char **)malloc((arr_size + 1) * sizeof(char *));
	if (!arr)
		return (NULL);
	if (!fill_arr(s, arr, c, arr_size))
		return (NULL);
	return (arr);
}
