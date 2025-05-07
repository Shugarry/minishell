/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frey-gal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 15:53:16 by frey-gal          #+#    #+#             */
/*   Updated: 2024/10/16 16:55:29 by frey-gal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*tmp;
	size_t	len;

	if (!s1 && !s2)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2);
	tmp = (char *)malloc((len + 1) * sizeof(char));
	if (tmp == NULL)
		return (NULL);
	ft_strlcpy(tmp, s1, ft_strlen(s1) + 1);
	ft_strlcat(tmp, s2, len + 1);
	return (tmp);
}
