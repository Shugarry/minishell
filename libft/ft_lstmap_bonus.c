/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miggarc2 <miggarc2@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 17:54:28 by miggarc2          #+#    #+#             */
/*   Updated: 2024/09/20 20:30:07 by miggarc2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*rslt_lst;
	t_list	*tmp_node;

	if (!f || !del)
		return (NULL);
	rslt_lst = NULL;
	while (lst)
	{
		tmp_node = ft_lstnew(f(lst->content));
		if (!tmp_node)
		{
			ft_lstclear(&rslt_lst, del);
			return (NULL);
		}
		ft_lstadd_back(&rslt_lst, tmp_node);
		lst = lst->next;
	}
	return (rslt_lst);
}
