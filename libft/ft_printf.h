/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frey-gal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 15:06:48 by frey-gal          #+#    #+#             */
/*   Updated: 2024/11/08 15:04:22 by frey-gal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdlib.h>
# include <stddef.h>
# include <limits.h>
# include <unistd.h>
# include <stdint.h>
# include <stdarg.h>

int	ft_printf(const char *format, ...);
int	print_base(int num, const char *base, int size, int i);
int	print_uns(unsigned int num, const char *base, unsigned int size, int i);
int	print_char(unsigned char c);
int	print_ptr(void *ptr);
int	print_str(const char *str);

#endif
