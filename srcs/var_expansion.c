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

typedef struct s_varlist
{
	char	*var_name;
	char	*content;
	struct s_varlist	*next;
}	t_varlist;

void	add_var_node(t_manager **memlist, t_varlist **head, char *var_name, char *content)
{
	t_varlist	*node;

	node = (t_varlist *)memlist_alloc(memlist, sizeof(t_varlist));
	if (!node)
		kill_and_exit(memlist, errno, "malloc failure");
	node->var_name = (char *)memlist_add(memlist, ft_strdup(var_name));
	if (!node->content)
		kill_and_exit(memlist, errno, "malloc failure");
	node->content = (char *)memlist_add(memlist, ft_strdup(content));
	if (!node->content)
		kill_and_exit(memlist, errno, "malloc failure");
	node->next = *head;
	*head = node;
}

void	remove_var_node(t_manager **memlist, t_varlist **head, char *var_name)
{
	int			i;
	t_varlist	*tmp;

	i = 0;
	tmp = *head;
	while (tmp)
	{
		if (str)
		tmp = tmp->next;
	}
}

t_varlist	*create_var_list(t_manager **memlist, char **env)
{
	t_varlist	*varlist;
	int			i;

	i = 0;
	varlist = NULL;
	while (env[i] != NULL)
	{
		add_var_node(memlist, &varlist, env[i]);
		i++;
	}
	return (varlist);
}
