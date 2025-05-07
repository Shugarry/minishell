/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frey-gal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 15:20:32 by frey-gal          #+#    #+#             */
/*   Updated: 2025/02/01 03:58:37 by frey-gal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print(char format, va_list args)
{
	if (format == 'c')
		return (print_char((char)va_arg(args, int)));
	if (format == 's')
		return (print_str(va_arg(args, char *)));
	if (format == 'p')
		return (print_ptr(va_arg(args, void *)));
	if (format == 'd' || format == 'i')
		return (print_base(va_arg(args, int), "0123456789", 10, 0));
	if (format == 'u')
		return (print_uns(va_arg(args, unsigned int), "0123456789", 10, 0));
	if (format == 'x')
		return (print_uns(va_arg(args, int), "0123456789abcdef", 16, 0));
	if (format == 'X')
		return (print_uns(va_arg(args, int), "0123456789ABCDEF", 16, 0));
	if (format == '%')
		return (print_char('%'));
	return (0);
}

int	scanner(const char *format, va_list args, int i)
{
	int	write_check;

	write_check = 0;
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			write_check = print(*format, args);
			if (write_check == -1)
				return (-1);
			i += write_check;
		}
		else
		{
			write_check = print_char(*format);
			if (write_check == -1)
				return (-1);
			i += write_check;
		}
		format++;
	}
	return (i);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		i;

	i = 0;
	va_start(args, format);
	i = scanner(format, args, i);
	va_end(args);
	return (i);
}
