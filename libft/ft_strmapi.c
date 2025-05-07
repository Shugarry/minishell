/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miggarc2 <miggarc2@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 17:54:28 by miggarc2          #+#    #+#             */
/*   Updated: 2024/09/16 19:36:08 by miggarc2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	len;
	char			*api;

	len = 0;
	while (s[len])
		len++;
	api = (char *)malloc(sizeof(char) * (len + 1));
	if (!api)
		return (0);
	api[len] = 0;
	while (len--)
		api [len] = f(len, s[len]);
	return (api);
}
