/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frey-gal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 16:32:42 by frey-gal          #+#    #+#             */
/*   Updated: 2024/12/20 18:35:09 by frey-gal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_base_deluxe(size_t num, const char *base, size_t size, int i)
{
	size_t	digit;

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
			i = print_base_deluxe(num / size, base, size, i);
		if (-1 == write(1, &base[digit], 1))
			return (-1);
		i++;
	}
	return (i);
}

int	print_ptr(void *ptr)
{
	size_t	address;
	int		i;

	i = 0;
	if (!ptr)
	{
		if (-1 == write(1, "(nil)", 5))
			return (-1);
		i += 5;
	}
	else
	{
		address = (size_t)ptr;
		if (-1 == write(1, "0x", 2))
			return (-1);
		i += 2;
		i = print_base_deluxe(address, "0123456789abcdef", 16, i);
	}
	return (i);
}
