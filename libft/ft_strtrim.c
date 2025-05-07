/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miggarc2 <miggarc2@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 17:54:28 by miggarc2          #+#    #+#             */
/*   Updated: 2025/03/03 19:46:30 by miggarc2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_is_set(char const c, char const *set)
{
	while (*set)
		if (*set++ == c)
			return (1);
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*trim;
	size_t	start;
	size_t	end;
	size_t	size;

	start = 0;
	end = 0;
	while (s1[start] && ft_is_set(s1[start], set))
		start++;
	while (s1[end])
		end++;
	end--;
	while (end > start && ft_is_set(s1[end], set))
		end--;
	size = end - start + 1;
	trim = (char *)malloc(sizeof(char) * (size + 1));
	if (!trim)
		return (0);
	trim[size] = 0;
	while (size-- > 0)
		trim[size] = s1[end--];
	return (trim);
}
