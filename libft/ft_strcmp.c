/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frey-gal <frey-gal@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 23:04:12 by frey-gal          #+#    #+#             */
/*   Updated: 2025/06/05 23:09:19 by frey-gal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;
	int		diff;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
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
