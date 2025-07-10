/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_env_helpers.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frey-gal <frey-gal@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 18:26:43 by frey-gal          #+#    #+#             */
/*   Updated: 2025/07/10 18:59:16 by frey-gal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	varlist_clean(t_var	*var)
{
	int	i;

	i = 0;
	if (!var->env)
		return ;
	while (var->env[i])
	{
		memlist_free_ptr(var, var->env[i]);
		var->env[i] = NULL;
		i++;
	}
	memlist_free_ptr(var, var->env);
	var->env = NULL;
}

void	add_env_var(t_var *var, char *variable)
{
	char	**new_varlist;
	int		i;

	var->env_len++;
	new_varlist = memlist_alloc(var, (var->env_len + 1) * sizeof(char *));
	i = 0;
	while (var->env && var->env[i])
	{
		new_varlist[i] = memlist_add(var, ft_strdup(var->env[i]));
		i++;
	}
	new_varlist[i] = memlist_add(var, ft_strdup(variable));
	i++;
	new_varlist[i] = NULL;
	varlist_clean(var);
	var->env = new_varlist;
}

bool	find_env_var(t_var *var, char *var_name)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(var_name);
	while (var->env[i])
	{
		if (ft_strncmp(var_name, var->env[i], len) == 0
			&& (var->env[i][len] == '=' || var->env[i][len] == '\0'))
			return (true);
		i++;
	}
	return (false);
}

void	remove_env_var(t_var *var, char *var_name)
{
	char	**new_varlist;
	int		len;
	int		i;
	int		j;

	if (!find_env_var(var, var_name))
		return ;
	var->env_len--;
	new_varlist = memlist_alloc(var, (var->env_len + 1) * sizeof(char *));
	i = 0;
	j = 0;
	len = ft_strlen(var_name);
	while (var->env && var->env[i])
	{
		if (ft_strncmp(var_name, var->env[i], len) == 0 \
			&& (var->env[i][len] == '=' || var->env[i][len] == '\0'))
		{
			i++;
			continue ;
		}
		new_varlist[j++] = memlist_add(var, ft_strdup(var->env[i++]));
	}
	new_varlist[j] = NULL;
	varlist_clean(var);
	var->env = new_varlist;
}

char	*get_env_var(t_var *var, char *var_name)
{
	int		i;
	int		len;
	char	*tmp;

	i = 0;
	len = ft_strlen(var_name);
	while (var->env && var->env[i])
	{
		if (ft_strncmp(var_name, var->env[i], len) == 0
			&& (var->env[i][len] == '=' || var->env[i][len] == '\0'))
		{
			tmp = ft_strchr(var->env[i], '=');
			if (!tmp || !tmp[1])
				return (NULL);
			else
				return (tmp + 1);
		}
		i++;
	}
	return (NULL);
}
