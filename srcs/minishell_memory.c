/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_manager.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frey-gal <frey-gal@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 19:50:38 by frey-gal          #+#    #+#             */
/*   Updated: 2025/06/04 19:50:39 by frey-gal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// ft_lstnew
void	*memlist_alloc(t_list **memlist, size_t size)
{
	t_list	*node;
	void	*ptr;

	if (!memlist)
		return (NULL);
	ptr = malloc(size);
	if (!ptr)
		return (NULL);
	node = (t_list *)malloc(sizeof(t_list));
	if (!node)
	{
		free(ptr);
		memlist_free_all(memlist);
		return (NULL);
		// pend ms_exit o ms_perror
	}
	node->content = ptr;
	node->next = *memlist;
	*memlist = node;
	return (ptr);
}

//ft_lstadd_front or ft_lstadd_back + ft_lstnew
void	*memlist_add(t_list **memlist, void *ptr)
{
	t_list	*node;

	if (!memlist)
		return (NULL);
	if (!ptr)
		return (NULL);
	node = (t_list *)malloc(sizeof(t_list));
	if (!node)
	{
		free(ptr);
		memlist_free_all(memlist);
		return (NULL);
		// pend ms_exit o ms_perror
	}
	node->content = ptr;
	node->next = *memlist;
	*memlist = node;
	return (ptr);
}

// ft_lstdelone
int	memlist_free_ptr(t_list **memlist, void *ptr) //TODO: Make shorter
{
	t_list	*current;
	t_list	*prev;

	if (!memlist || !ptr || !*memlist)
		return (0);
	if ((*memlist)->content == ptr)
	{
		current = *memlist;
		*memlist = (*memlist)->next;
		free(current->content);
		free(current);
		return (1);
	}
	prev = *memlist;
	current = (*memlist)->next;
	while (current)
	{
		if (current->content == ptr)
		{
			prev->next = current->next;
			free(current->content);
			free(current);
			return (1);
		}
		prev = current;
		current = current->next;
	}
	return (1);
}

// use ft_lstclear(t_list **memlist, free);
int	memlist_free_all(t_list **memlist)
{
	t_list	*current;
	t_list	*next;
	int		i;

	i = 0;
	if (!memlist || !*memlist)
		return (0);
	current = *memlist;
	while (current)
	{
		next = current->next;
		free(current->content);
		free(current);
		i++;
		current = next;
	}
	*memlist = NULL;
	return (i);
}
