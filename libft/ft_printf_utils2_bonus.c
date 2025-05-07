/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils2_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miggarc2 <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 00:00:34 by miggarc2          #+#    #+#             */
/*   Updated: 2024/12/21 19:36:13 by miggarc2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

_Bool	ft_wrt_chr(t_args *args, int *max, int size, char c);

static _Bool	ft_frmt_hex(t_args *args, long hex, int size, char c)
{
	int	tmp;

	tmp = 1;
	if (!args->dash && !args->dot && c != 'p' && !args->sharp && args->zero)
		tmp = ft_wrt_chr(args, &args->width, args->prec, '0');
	else if (!args->dash && (!args->zero || (args->zero && args->dot)))
		tmp = ft_wrt_chr(args, &args->width, args->prec, ' ');
	if (!tmp)
		return (0);
	if (hex && (c == 'p' || (args->sharp && (c == 'x' || c == 'X'))))
	{
		if (c == 'X' && write (1, "0X", 2) < 0)
			return (0);
		else if (c != 'X' && write (1, "0x", 2) < 0)
			return (0);
		args->len += 2;
	}
	if (!args->dash && !args->dot && args->width - args->prec > 0)
		tmp = args->prec + (args->width - args->prec);
	else
		tmp = args->prec;
	if (!ft_wrt_chr(args, &tmp, size, '0'))
		return (0);
	return (1);
}

static _Bool	ft_put_hex(t_args *args, uintptr_t hex, char c)
{
	int		wrt;
	char	ch;

	if (hex > 15 && !ft_put_hex(args, hex / 16, c))
		return (0);
	if (!hex)
	{
		if (c == 'p')
			wrt = write(1, "(nil)", 5);
		else if (args->dot && !args->prec)
			wrt = 0;
		else
			wrt = write(1, "0", 1);
	}
	else
	{
		ch = "0123456789abcdef"[hex % 16];
		if (c == 'X')
			ch = ft_toupper(ch);
		wrt = write(1, &ch, 1);
	}
	if (wrt < 0)
		return (0);
	args->len += wrt;
	return (1);
}

_Bool	ft_mng_hex(t_args *args, uintptr_t hex, char c)
{
	int			size;
	uintptr_t	tmp;

	size = 0;
	if (hex == 0 && c == 'p')
		size += 4;
	else if (hex == 0 && !(args->dot && !args->prec))
		size++;
	tmp = hex;
	while (tmp && ++size)
		tmp /= 16;
	if (args->width < size)
		args->width = size;
	if (args->prec < size)
		args->prec = size;
	if (c == 'p' || (args->sharp && (c == 'x' || c == 'X')))
		if (--args->width > size && hex)
			args->width--;
	if (!ft_frmt_hex(args, hex, size, c) || !ft_put_hex(args, hex, c))
		return (0);
	if (args->dash && !ft_wrt_chr(args, &args->width, args->prec, ' '))
		return (0);
	return (1);
}

static _Bool	ft_frmt_dec(t_args *args, long *dec, int size, char c)
{
	int		tmp;
	char	ch;

	tmp = args->prec;
	if ((c == 'd' || c == 'i') && (*dec < 0 || args->plus || args->blk))
	{
		ch = '-';
		if (*dec < 0)
			*dec *= -1;
		else if (args->plus)
			ch = '+';
		else if (args->blk)
			ch = ' ';
		if (write(1, &ch, 1) < 0)
			return (0);
		args->len++;
	}
	if (!args->dash && (args->zero || args->dot))
		if (!ft_wrt_chr(args, &args->width, args->prec, '0'))
			return (0);
	if (!ft_wrt_chr(args, &tmp, size, '0'))
		return (0);
	return (1);
}

_Bool	ft_put_dec(t_args *args, long dec, int size, char c)
{
	char	ch;

	if (c && !ft_frmt_dec(args, &dec, size, c))
		return (0);
	if (dec > 9 && !ft_put_dec(args, dec / 10, 0, 0))
		return (0);
	else if (args->dot && !args->prec)
		return (1);
	ch = dec % 10 + 48;
	if (write(1, &ch, 1) < 0)
		return (0);
	args->len++;
	return (1);
}
