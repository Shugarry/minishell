/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frey-gal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 18:29:46 by frey-gal          #+#    #+#             */
/*   Updated: 2024/10/16 16:56:15 by frey-gal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int			flag;
	int			i;

	i = 0;
	flag = 0;
	while (s[i])
	{
		if (s[i] == (unsigned char)c)
			flag = i;
		i++;
	}
	if (flag || s[0] == (unsigned char)c)
		return ((char *)s + flag);
	if ((unsigned char)c == 0)
		return ((char *)s + i);
	return (NULL);
}
