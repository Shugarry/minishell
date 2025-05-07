/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frey-gal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 13:04:20 by frey-gal          #+#    #+#             */
/*   Updated: 2024/10/16 16:59:50 by frey-gal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

int	ft_atoi(const char *nptr)
{
	int	n;
	int	flag;

	flag = 0;
	n = 0;
	while ((*nptr <= 13 && *nptr >= 9) || *nptr == 32)
		nptr++;
	if (ft_strncmp(nptr, "-2147483648", 11) == 0)
		return (-2147483648);
	if (*nptr == '+')
		nptr++;
	else if (*nptr == '-')
	{
		nptr++;
		flag++;
	}
	while (ft_isdigit(*nptr))
	{
		n *= 10;
		n = n + (*nptr++ - '0');
	}
	if (flag)
		n = -n;
	return (n);
}
