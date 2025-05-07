/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frey-gal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 19:03:50 by frey-gal          #+#    #+#             */
/*   Updated: 2024/10/16 16:54:25 by frey-gal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const char	*t1;
	const char	*t2;
	size_t		i;

	i = 0;
	t1 = (const char *)s1;
	t2 = (const char *)s2;
	while (i < n)
	{
		if ((unsigned char)t1[i] > (unsigned char)t2[i])
			return (1);
		if ((unsigned char)t1[i] < (unsigned char)t2[i])
			return (-1);
		i++;
	}
	return (0);
}
