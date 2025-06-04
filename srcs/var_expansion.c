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

void	add_var_node(t_manager **memlist, t_varlist **head, char *var_name, char *content)
{
	t_varlist	*node;

	node = (t_varlist *)memlist_alloc(memlist, sizeof(t_varlist));
	if (!node)
		kill_and_exit(memlist, errno, "malloc failure");
	node->var_name = (char *)memlist_add(memlist, ft_strdup(var_name));
	if (!node->var_name)
		kill_and_exit(memlist, errno, "malloc failure");
	if (content)
	{
		node->content = (char *)memlist_add(memlist, ft_strdup(content));
		if (!node->content)
			kill_and_exit(memlist, errno, "malloc failure");
	}
	else
		node->content = NULL;
	node->next = *head;
	*head = node;
}

int	remove_var_node(t_manager **memlist, t_varlist **head, char *var_name) // NOTE: function too long gotta fix
{
	int			i;
	t_varlist	*prev;
	t_varlist	*curr;

	i = 0;
	prev = *head;
	if (ft_strncmp(prev->var_name, var_name, ft_strlen(var_name) + 1 == 0))
	{
		*head = (*head)->next;
		free(prev->content);
		free(prev->var_name);
		return 0;
	}
	curr = (*head)->next;
	while (curr)
	{
		if (ft_strncmp(curr->var_name, var_name, ft_strlen(var_name) + 1 == 0))
		{
			prev->next = curr->next;
			free(curr->var_name);
			free(curr->content);
			free (curr);
			return (0);
		}
		prev = curr;
		curr = curr->next;
	}
	return 1;
}

t_varlist	*create_var_list(t_manager **memlist, char **env)
{
	t_varlist	*varlist;
	char		*env_var;
	char		*var_content;
	int			i;

	i = 0;
	varlist = NULL;
	while (env[i] != NULL)
	{
		env_var = (char *)memlist_add(memlist, ft_strdup(env[i]));
		if (!env_var)
			kill_and_exit(memlist, EXIT_FAILURE, "malloc failure");
		var_content = ft_strchr(env_var, '=');
		var_content[0] = '\0';
		var_content++;
		if (*var_content == '\0')
			add_var_node(memlist, &varlist, env_var, NULL);
		else
			add_var_node(memlist, &varlist, env_var, var_content);
		memlist_free_ptr(memlist, env_var);
		i++;
	}
	return (varlist);
}
