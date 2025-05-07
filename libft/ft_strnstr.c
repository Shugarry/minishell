/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frey-gal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 19:13:31 by frey-gal          #+#    #+#             */
/*   Updated: 2024/10/16 16:56:09 by frey-gal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (!big || !little)
		return (NULL);
	if (!*little)
		return ((char *)big);
	while (i < len && big[i])
	{
		j = 0;
		while (big[i + j] && little[j])
		{
			if (i + j < len && big[i + j] == little[j])
				j++;
			else
				break ;
		}
		if (!little[j])
			return ((char *)big + i);
		i++;
	}
	return (NULL);
}
