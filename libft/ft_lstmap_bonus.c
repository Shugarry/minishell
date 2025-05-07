/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frey-gal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 21:47:05 by frey-gal          #+#    #+#             */
/*   Updated: 2024/10/17 18:24:25 by frey-gal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*head;
	t_list	*node;
	void	*content;

	if (f == NULL || del == NULL)
		return (NULL);
	head = NULL;
	while (lst)
	{
		content = f(lst->content);
		node = ft_lstnew(content);
		if (node == NULL)
		{
			ft_lstclear(&head, del);
			del(content);
			return (NULL);
		}
		ft_lstadd_back(&head, node);
		lst = lst->next;
	}
	return (head);
}
