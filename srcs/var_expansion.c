/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expansion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frey-gal <frey-gal@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 12:11:29 by frey-gal          #+#    #+#             */
/*   Updated: 2025/05/14 22:55:42 by frey-gal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

typedef struct s_varlist {
	char	*content;
	bool	is_num;
	struct s_varlist	*next;
}	t_varlist;

t_varlist	*add_var_node(t_manager **memlist, t_varlist **head, char *content)
{
	t_manager	*node;

	if (!memlist)
		return (NULL);
	content = (char *)memlist_add(memlist, ft_strdup(content));
	if (!content)
	{
		memlist_free_all(memlist);
		return (NULL);
	}
	node = (t_varlist *)memlist_alloc(memlist, sizeof(t_varlist));
	if (!node)
	{
		return (NULL);
	}
	node->ptr = ptr;
	node->next = *memlist;
	*memlist = node;
	return (ptr);
}
