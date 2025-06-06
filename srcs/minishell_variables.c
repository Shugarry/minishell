/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_variables.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frey-gal <frey-gal@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 12:11:29 by frey-gal          #+#    #+#             */
/*   Updated: 2025/06/06 04:43:22 by frey-gal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	add_var_node(t_var *var, char *var_name, char *content)
{
	t_varlist	*node;

	node = (t_varlist *)memlist_alloc(&var->memlist, sizeof(t_varlist));
	if (!node)
		ms_exit(var, ms_perror("", strerror(errno), "", errno));
	node->var_name = (char *)memlist_add(&var->memlist, ft_strdup(var_name));
	if (!node->var_name)
		ms_exit(var, ms_perror("", strerror(errno), "", errno));
	if (content)
	{
		node->content = (char *)memlist_add(&var->memlist, ft_strdup(content));
		if (!node->content)
			ms_exit(var, ms_perror("", strerror(errno), "", errno));
	}
	else
		node->content = NULL;
	node->next = var->varlist;
	var->varlist = node;
	return (1);
}

int	remove_var_node(t_var *var, char *var_name)
{
	t_varlist	*prev;
	t_varlist	*curr;

	prev = var->varlist;
	if (ft_strcmp(prev->var_name, var_name) == 0)
	{
		var->varlist = var->varlist->next;
		memlist_free_ptr(&var->memlist, prev->content);
		memlist_free_ptr(&var->memlist, prev->var_name);
		return (1);
	}
	curr = var->varlist->next;
	while (curr)
	{
		if (ft_strcmp(curr->var_name, var_name) == 0)
		{
			prev->next = curr->next;
			memlist_free_ptr(&var->memlist, curr->var_name);
			memlist_free_ptr(&var->memlist, curr->content);
			memlist_free_ptr(&var->memlist, curr);
			return (1);
		}
		prev = curr;
		curr = curr->next;
	}
	return (0);
}

char	*get_var_content(t_var *var, char *variable)
{
	t_varlist *head;

	head = var->varlist;
	while (head != NULL)
	{
		if (ft_strcmp(head->var_name, variable) == 0)
			return (head->content);
		head = head->next;
	}
	return (NULL);
}

int		modify_var_content(t_var *var, char *var_name, char *new_content)
{
	t_varlist	*curr;

	curr = var->varlist;
	while (curr)
	{
		if (ft_strcmp(curr->var_name, var_name) == 0)
		{
			memlist_free_ptr(&var->memlist, curr->content);
			curr->content = NULL;
			if (new_content)
				curr->content = (char *)memlist_add(&var->memlist, ft_strdup(new_content));
			if (!curr->content && new_content)
				ms_exit(var, ms_perror("", "malloc fail()", "", errno));
			return (1);
		}
		curr = curr->next;
	}
	return (add_var_node(var, var_name, new_content));
}

void	create_var_list(t_var *var, char **env)
{
	char		*env_var;
	char		*var_content;
	int			i;

	i = 0;
	var->varlist = NULL;
	while (env[i] != NULL)
	{
		env_var = (char *)memlist_add(&var->memlist, ft_strdup(env[i]));
		if (!env_var)
			ms_exit(var, ms_perror("", strerror(errno), "", errno));
		var_content = ft_strchr(env_var, '=');
		var_content[0] = '\0';
		var_content++;
		if (*var_content == '\0')
			add_var_node(var, env_var, NULL);
		else
			add_var_node(var, env_var, var_content);
		memlist_free_ptr(&var->memlist, env_var);
		i++;
	}
}
