/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_manager.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miggarc2 <miggarc2@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 18:15:18 by miggarc2          #+#    #+#             */
/*   Updated: 2025/05/28 18:15:23 by miggarc2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// This function seems to be a ft_lstnew but with malloc for content, 
//can we use ft_lstnew instead?
void	*memlist_alloc(t_list **head, size_t size)
{
	t_list	*node;
	void	*content;

	if (!head)
		return (NULL);
	content = malloc(size);
	if (!content)
		return (NULL);
	node = (t_list *)malloc(sizeof(t_list));
	if (!node)
	{
		free(content);
		return (NULL);
	}
	node->content = content;
	node->next = *head;
	*head = node;
	return (content);
}

// This function seems too similar to ft_lstnew, can we use it instead?
void	*memlist_add(t_list **head, void *content)
{
	t_list	*node;

	if (!head)
		return (NULL);
	if (!content)
		return (NULL);
	node = (t_list *)malloc(sizeof(t_list));
	if (!node)
	{
		free(content);
		return (NULL);
	}
	node->content = content;
	node->next = *head;
	*head = node;
	return (content);
}

// I don't understand completely this function, ask Felix about it
//TODO: Make shorter for norminette
int	memlist_free_content(t_list **head, void *content)
{
	t_list	*current;
	t_list	*prev;

	if (!head || !content || !*head)
		return (0);
	if ((*head)->content == content)
	{
		current = *head;
		*head = (*head)->next;
		free(current->content);
		free(current);
		return (1);
	}
	prev = *head;
	current = (*head)->next;
	while (current)
	{
		if (current->content == content)
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

// This function can be replaced using ft_lstclear(&head, free);
int	memlist_free_all(t_list **head)
{
	t_list	*current;
	t_list	*next;
	int		i;

	i = 0;
	if (!head || !*head)
		return (0);
	current = *head;
	while (current)
	{
		next = current->next;
		free(current->content);
		free(current);
		i++;
		current = next;
	}
	*head = NULL;
	return (i);
}
