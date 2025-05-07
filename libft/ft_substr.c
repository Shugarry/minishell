/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frey-gal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 15:40:31 by frey-gal          #+#    #+#             */
/*   Updated: 2024/10/16 16:56:27 by frey-gal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*tmp;
	size_t	i;

	if (!s)
		return (NULL);
	if (ft_strlen(s) <= start)
		return (ft_strdup(""));
	if (len > ft_strlen(s) - start)
		len = ft_strlen(s) - start;
	i = 0;
	tmp = (char *)malloc((len + 1) * sizeof(char));
	if (tmp == NULL)
		return (NULL);
	while (i < len && s[i + start])
	{
		tmp[i] = s[i + start];
		i++;
	}
	tmp[i] = '\0';
	return (tmp);
}
