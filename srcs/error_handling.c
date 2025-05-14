/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frey-gal <frey-gal@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 19:23:14 by frey-gal          #+#    #+#             */
/*   Updated: 2025/05/12 19:27:36 by frey-gal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	kill_and_exit(t_manager **head, int status, char *message)
{
	if (message != NULL)
		printf("%s: %s\n", message, strerror(errno));
	memlist_free_all(head);
	exit(EXIT_FAILURE);
}
