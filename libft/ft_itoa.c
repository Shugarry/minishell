/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miggarc2 <miggarc2@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 17:54:28 by miggarc2          #+#    #+#             */
/*   Updated: 2025/06/24 14:22:17 by miggarc2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_nbr_size(int n)
{
	size_t			size;
	unsigned int	unb;

	size = 1;
	if (n < 0)
	{
		size++;
		unb = -n;
	}
	else
		unb = n;
	while (unb >= 10)
	{
		size++;
		unb /= 10;
	}
	return (size);
}

static void	ft_fill_nbr(char *nbr, int n, int size)
{
	unsigned int	unb;

	nbr[size] = 0;
	if (n < 0)
	{
		unb = -n;
		nbr[0] = 45;
	}
	else
		unb = n;
	while (size-- > 0)
	{
		if (n < 0 && nbr[size] == 45)
			break ;
		nbr[size] = unb % 10 + 48;
		unb /= 10;
	}
}

char	*ft_itoa(int n)
{
	char			*nbr;
	int				size;

	size = ft_nbr_size(n);
	nbr = (char *)malloc(sizeof(char) * (size + 1));
	if (!nbr)
		return (NULL);
	ft_fill_nbr(nbr, n, size);
	return (nbr);
}
