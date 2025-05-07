/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_uns.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frey-gal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 16:41:53 by frey-gal          #+#    #+#             */
/*   Updated: 2024/12/20 18:35:22 by frey-gal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_uns(unsigned int num, const char *base, unsigned int size, int i)
{
	unsigned int	digit;

	if (num == 0)
	{
		if (-1 == write(1, "0", 1))
			return (-1);
		return (1 + i);
	}
	if (num / size != 0 || num % size != 0)
	{
		digit = num % size;
		if (num / size)
			i = print_uns(num / size, base, size, i);
		if (-1 == write(1, &base[digit], 1))
			return (-1);
		i++;
	}
	return (i);
}
