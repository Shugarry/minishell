/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frey-gal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 16:37:11 by frey-gal          #+#    #+#             */
/*   Updated: 2024/10/16 16:56:21 by frey-gal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

size_t	find_end(const char *s1, const char *set)
{
	size_t	len;

	len = ft_strlen(s1);
	while (0 < len && ft_strchr(set, s1[len - 1]))
		len--;
	return (len);
}

char	*ft_strtrim(const char *s1, const char *set)
{
	size_t	i;
	size_t	len;
	char	*tmp;

	i = 0;
	if (!s1)
		return (NULL);
	while (s1[i] && ft_strchr(set, s1[i]))
		i++;
	len = find_end(s1 + i, set);
	tmp = (char *)malloc((len + 1) * sizeof(char));
	if (tmp == NULL)
		return (NULL);
	ft_strlcpy(tmp, s1 + i, len + 1);
	return (tmp);
}
