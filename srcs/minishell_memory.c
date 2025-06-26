/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_memory.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frey-gal <frey-gal@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 19:50:38 by frey-gal          #+#    #+#             */
/*   Updated: 2025/06/26 01:06:39 by frey-gal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	*memlist_alloc(t_var *var, size_t size)
{
	t_list	*node;
	void	*ptr;

	if (!var)
		return (NULL);
	ptr = malloc(size);
	if (!ptr)
		ms_exit(var, ms_perror("", "malloc() fail", "", errno));
	node = ft_lstnew(ptr);
	if (!node)
	{
		free(ptr);
		ms_exit(var, ms_perror("", "malloc() fail", "", errno));
	}
	ft_lstadd_front(&var->memlist, node);
	return (ptr);
}

void	*memlist_add(t_var *var, void *ptr)
{
	t_list	*node;

	if (!var)
		return (NULL);
	if (!ptr)
		return (NULL);
	node = ft_lstnew(ptr);
	if (!node)
	{
		free(ptr);
		ms_exit(var, ms_perror("", "malloc() fail", "", errno));
	}
	ft_lstadd_front(&var->memlist, node);
	return (ptr);
}

void	memlist_free_ptr(t_var *var, void *ptr)
{
	t_list	*current;
	t_list	*prev;

	if (!var || !ptr || !var->memlist)
		return ;
	if ((var->memlist)->content == ptr)
	{
		current = var->memlist;
		var->memlist = (var->memlist)->next;
		ft_lstdelone(current, free);
		return ;
	}
	prev = var->memlist;
	current = (var->memlist)->next;
	while (current)
	{
		if (current->content == ptr)
		{
			prev->next = current->next;
			ft_lstdelone(current, free);
			return ;
		}
		prev = current;
		current = current->next;
	}
}

void	memlist_free_all(t_var *var)
{
	if (!var || !var->memlist)
		return ;
	ft_lstclear(&var->memlist, free);
}
