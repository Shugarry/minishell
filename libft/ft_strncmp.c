/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miggarc2 <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 18:19:05 by miggarc2          #+#    #+#             */
/*   Updated: 2025/03/24 22:47:04 by miggarc2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;
	int		diff;

	if (!n)
		return (0);
	i = 0;
	while (i + 1 < n && s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	diff = (unsigned char)s1[i] - (unsigned char)s2[i];
	if ((s1[i] >= ' ' && s1[i] <= '~') && (s2[i] >= ' ' && s2[i] <= '~'))
		return (diff);
	else if (diff < 0)
		return (-1);
	else if (diff > 0)
		return (1);
	return (0);
}
