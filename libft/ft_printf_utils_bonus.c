/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miggarc2 <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 00:00:34 by miggarc2          #+#    #+#             */
/*   Updated: 2025/02/16 20:56:27 by miggarc2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

_Bool	ft_wrt_chr(t_args *args, int *max, int size, char c);

_Bool	ft_mng_hex(t_args *args, long dec, char c);

_Bool	ft_put_dec(t_args *args, long dec, int size, char c);

_Bool	ft_mng_dec(t_args *args, long dec, char c)
{
	int		size;
	long	tmp;

	size = 0;
	if (dec < 0 || args->blk || args->plus)
		args->width--;
	if (dec == 0 && !(args->dot && !args->prec))
		size++;
	tmp = dec;
	while (tmp && ++size)
		tmp /= 10;
	if (args->width < size)
		args->width = size;
	if (args->prec < size)
		args->prec = size;
	if (!args->dash && (args->dot || !args->zero))
		if (!ft_wrt_chr(args, &args->width, args->prec, ' '))
			return (0);
	if (!ft_put_dec(args, dec, size, c))
		return (0);
	if (args->dash)
		if (!ft_wrt_chr(args, &args->width, args->prec, ' '))
			return (0);
	return (1);
}

_Bool	ft_wrt_chr(t_args *args, int *max, int size, char c)
{
	int	wrt;

	while (*max > size)
	{
		wrt = write (1, &c, 1);
		if (wrt < 0)
			return (0);
		args->len++;
		(*max)--;
	}
	return (1);
}

static _Bool	ft_wrt_c(t_args *args, char c)
{
	int	wrt;

	if (!args->dash)
		if (!ft_wrt_chr(args, &args->width, 1, ' '))
			return (0);
	wrt = write (1, &c, 1);
	if (wrt < 0)
		return (0);
	args->len++;
	if (!ft_wrt_chr(args, &args->width, 1, ' '))
		return (0);
	return (1);
}

_Bool	ft_wrt_s(t_args *args, char *str)
{
	int	wrt;
	int	len;

	if (!str)
	{
		if (args->dot && args->prec < 6)
			str = "";
		else
			str = "(null)";
	}
	len = ft_strlen(str);
	if (args->dot && len > args->prec)
		len = args->prec;
	if (!args->dash)
		if (!ft_wrt_chr(args, &args->width, len, ' '))
			return (0);
	wrt = write(1, str, len);
	if (wrt < 0)
		return (0);
	args->len += wrt;
	if (!ft_wrt_chr(args, &args->width, len, ' '))
		return (0);
	return (1);
}

_Bool	ft_conv(t_args *args, char *fmt)
{
	_Bool	flag;

	if (*fmt == '\0')
		return (0);
	if (*fmt == 'c')
		flag = ft_wrt_c(args, va_arg(args->ap, int));
	else if (*fmt == 's')
		flag = ft_wrt_s(args, va_arg(args->ap, char *));
	else if (*fmt == 'p')
		flag = ft_mng_hex(args, va_arg(args->ap, intptr_t), *fmt);
	else if (*fmt == 'd' || *fmt == 'i')
		flag = ft_mng_dec(args, va_arg(args->ap, int), *fmt);
	else if (*fmt == 'u')
		flag = ft_mng_dec(args, va_arg(args->ap, unsigned int), *fmt);
	else if (*fmt == 'x' || *fmt == 'X')
		flag = ft_mng_hex(args, va_arg(args->ap, unsigned int), *fmt);
	else if (*fmt == '%')
		flag = ft_wrt_c(args, '%');
	else
	{
		flag = ft_wrt_c(args, '%');
		args->i = 0;
	}
	args->i++;
	return (flag);
}
