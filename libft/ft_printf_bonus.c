/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miggarc2 <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 00:00:34 by miggarc2          #+#    #+#             */
/*   Updated: 2024/12/21 19:34:58 by miggarc2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

_Bool	ft_conv(t_args *args, char *fmt);

static int	ft_find_width_prec(t_args *args, char *fmt)
{
	int	len;

	len = 0;
	if (fmt[len] >= '0' && fmt[len] <= '9')
		args->width = ft_atoi(fmt);
	while (fmt[len] >= '0' && fmt[len] <= '9')
		len++;
	if (fmt[len] == '.')
	{
		args->dot = 1;
		args->prec = ft_atoi(fmt + (++len));
	}
	while (fmt[len] >= '0' && fmt[len] <= '9')
		len++;
	return (len);
}

static void	ft_clean_flags(t_args *args)
{
	args->dash = 0;
	args->zero = 0;
	args->sharp = 0;
	args->blk = 0;
	args->plus = 0;
	args->dot = 0;
	args->width = 0;
	args->prec = 0;
}

static _Bool	ft_find_flags(t_args *args, char *fmt)
{
	args->i = 0;
	if (fmt[args->i] != '%')
		return (1);
	while (fmt[args->i++])
	{
		if (fmt[args->i] == '-')
			args->dash = 1;
		else if (fmt[args->i] == '0')
			args->zero = 1;
		else if (fmt[args->i] == '#')
			args->sharp = 1;
		else if (fmt[args->i] == ' ')
			args->blk = 1;
		else if (fmt[args->i] == '+')
			args->plus = 1;
		else
			break ;
	}
	args->i += ft_find_width_prec(args, &fmt[args->i]);
	if (!ft_conv(args, fmt + args->i))
		return (0);
	ft_clean_flags(args);
	return (1);
}

static _Bool	ft_wrt_reg(t_args *args, char *fmt)
{
	int	wrt;

	args->i = 0;
	while (fmt[args->i] && fmt[args->i] != '%')
		args->i++;
	wrt = write(1, fmt, args->i);
	if (wrt < 0)
		return (0);
	args->len += wrt;
	return (1);
}

int	ft_printf(char const *fmt, ...)
{
	t_args	args;
	char	*tmp;

	ft_bzero(&args, sizeof(t_args));
	tmp = (char *)fmt;
	va_start(args.ap, fmt);
	while (*tmp)
	{
		if (!ft_find_flags(&args, tmp))
		{
			args.len = -1;
			break ;
		}
		tmp += args.i;
		if (!ft_wrt_reg(&args, tmp))
		{
			args.len = -1;
			break ;
		}
		tmp += args.i;
	}
	va_end(args.ap);
	return (args.len);
}
/*
#include <stdio.h>

int	main(void)
{
	char		*s1 = NULL;
	char		*s2 = "Hola mundo!";
	char		c[2] = {'K', 'u'};
	int			nbr[4] = {2147483647, -2147483648, 0, 42};

	printf("orig: Hola\n");
	printf("orig: %s", "mundo\n");
	printf("orig: %i\n", 42);
	printf("orig: %#5x\n", 16);
	printf("orig: %p\n", "84");
	printf("orig: %c hola\n", 3);
	printf("orig: %10p\n", s2);
	printf("orig: %#020.015X\n", s2);
	printf("orig: %#020.015u\n", s2);
	printf("orig: %-#8c\n", 72);
	printf("orig: %-#.8d hola\n", 30);
	printf("orig: %-#.8k hola\n", 30);

	ft_printf("mine: Hola\n");
	ft_printf("mine: %s", "mundo\n");
	ft_printf("mine: %i\n", 42);
	ft_printf("mine: %#5x\n", 16);
	ft_printf("mine: %p\n", "84");
	ft_printf("mine: %c hola\n", 3);
	ft_printf("mine: %10p\n", s2);
	ft_printf("mine: %#020.015X\n", s2);
	ft_printf("orig: %#020.015u\n", s2);
	ft_printf("mine: %-#8c\n", 72);
	ft_printf("mine: %-#.8d hola\n", 30);
	ft_printf("mine: %-#.8k hola\n", 30);


	write(1, "\nTest 0:\n", 9);
	ft_putnbr_fd(printf("orig: Hola\n"), 1);
	ft_putnbr_fd(ft_printf("mine: Hola\n"), 1);

	write(1, "\nTest 1:\n", 9);
	ft_putnbr_fd(printf("orig: %u, %d, %#X, %-p, %s, %c, %% \n", \
			nbr[0], nbr[1], nbr[2], s2, s1, c[1]), 1);
	write(1, "\n", 1);
	ft_putnbr_fd(ft_printf("mine: %u, %d, %#X, %-p, %s, %c, %% \n", \
			nbr[0], nbr[1], nbr[2], s2, s1, c[1]), 1);
	write(1, "\n", 1);

	write(1, "\nTest 2:\n", 9);
	printf("orig: %x\n", 18446744073709551615);
	ft_printf("mine: %x\n", 18446744073709551615);
	
	write(1, "\nTest 3:\n", 9);
	printf("orig: %5s\n", s2);
	ft_printf("mine: %5s\n", s2);
	
	write(1, "\nTest 4:\n", 9);
	printf("orig: %.8s\n", s2);
	ft_printf("mine: %.8s\n", s2);

	write(1, "\nTest 5:\n", 9);
	printf("orig: %#2.5x\n", &s2);
	ft_printf("mine: %#2.5x\n", &s2);

	write(1, "\nTest 6:\n", 9);
    printf("orig: %-.p\n", (void *)0);
    ft_printf("mine: %-.p\n", (void *)0);

	write(1, "\nTest 7:\n", 9);
    printf("orig: %05x\n", nbr[3]);
    ft_printf("mine: %05x\n", nbr[3]);

	write(1, "\nTest 8:\n", 9);
    printf("orig: %#0.9x\n", nbr[3]);
    ft_printf("mine: %#0.9x\n", nbr[3]);

	write(1, "\nTest 9:\n", 9);
    printf("orig: %0.9d\n", nbr[3]);
    ft_printf("mine: %0.9d\n", nbr[3]);

	write(1, "\nTest 10:\n", 10);
    printf("orig: '% i'\n", nbr[2] - 2);
    ft_printf("mine: '% i'\n", nbr[2] - 2);

	write(1, "\nTest 11:\n", 10);
    printf("orig: '% +d'\n", 89);
    ft_printf("mine: '% +d'\n", 89);

	write(1, "\nTest 12:\n", 10);
    printf("orig: %#.X\n", (void *)0);
    ft_printf("mine: %#.X\n", (void *)0);

	write(1, "\nTest 13:\n", 10);
    printf("orig: %-+ #.s\n", "string");
    ft_printf("mine: %-+ #.s\n", "string");

	write(1, "\nTest 14:\n", 10);
    printf("orig: final%", "final%");
	ft_printf("\nmine: final%", "final%");

	write(1, "\nTest 15:\n", 10);
    printf("orig: %%%%%", "final%");
    ft_printf("\nmine: %%%%%", "final%");

	write(1, "\nTest 16:\n", 10);
    ft_printf("%%%%%");
    write(1, "\n", 1);
	printf("%%%%%");
}
*/
