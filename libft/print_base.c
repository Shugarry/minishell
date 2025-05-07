/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_base.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frey-gal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 16:41:53 by frey-gal          #+#    #+#             */
/*   Updated: 2024/12/20 18:34:51 by frey-gal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	check_cases(int num)
{
	if (num == INT_MIN)
	{
		if (-1 == write(1, "-2147483648", 11))
			return (-1);
		return (11);
	}
	if (num == 0)
	{
		if (-1 == write(1, "0", 1))
			return (-1);
		return (1);
	}
	return (0);
}

int	print_base(int num, const char *base, int size, int i)
{
	int	digit;
	int	cases;

	cases = check_cases(num);
	if (cases == -1)
		return (-1);
	else if (cases)
		return (cases + i);
	if (num < 0)
	{
		if (-1 == write(1, "-", 1))
			return (-1);
		i++;
		num = -num;
	}
	if (num / size != 0 || num % size != 0)
	{
		digit = num % size;
		if (num / size)
			i = print_base(num / size, base, size, i);
		if (-1 == write(1, &base[digit], 1))
			return (-1);
		i++;
	}
	return (i);
}
