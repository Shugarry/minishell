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

void	varlist_clean(t_var	*var)
{
	int	i;

	i = 0;
	if (!var->env)
		return ;
	while (var->env[i])
	{
		memlist_free_ptr(&var->memlist, var->env[i]);
		var->env[i] = NULL;
		i++;
	}
	memlist_free_ptr(&var->memlist, var->env);
	var->env = NULL;
}

void	add_env_var(t_var *var, char *variable)
{
	char	**new_varlist;
	int		i;
	
	var->env_len++;
	new_varlist = (char **)memlist_alloc(&var->memlist, (var->env_len + 1) * sizeof(char *));
	if (!new_varlist)
		ms_exit(var, ms_perror("", "malloc fail()", "", errno));
	i = 0;
	while (var->env && var->env[i])
	{
		new_varlist[i] = (char *)memlist_add(&var->memlist, ft_strdup(var->env[i]));
		if (!new_varlist[i])
			ms_exit(var, ms_perror("", "malloc fail()", "", errno));
		i++;
	}
	new_varlist[i] = (char *)memlist_add(&var->memlist, ft_strdup(variable));
	if (!new_varlist[i])
		ms_exit(var, ms_perror("", "malloc fail()", "", errno));
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
		if (ft_strncmp(var_name, var->env[i], len) == 0 &&
			(var->env[i][len] == '=' || var->env[i][len] == '\0'))
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
	new_varlist = (char **)memlist_alloc(&var->memlist, (var->env_len + 1) * sizeof(char *));
	if (!new_varlist)
		ms_exit(var, ms_perror("", "malloc fail()", "", errno));
	i = 0;
	j = 0;
	len = ft_strlen(var_name);
	while (var->env && var->env[i])
	{
		if (ft_strncmp(var_name, var->env[i], len) == 0 &&
			(var->env[i][len] == '=' || var->env[i][len] == '\0'))
		{
			i++;
			continue ;
		}
		new_varlist[j] = (char *)memlist_add(&var->memlist, ft_strdup(var->env[i]));
		if (!new_varlist[j])
			ms_exit(var, ms_perror("", "malloc fail()", "", errno));
		j++;
		i++;
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
		if (ft_strncmp(var_name, var->env[i], len) == 0 &&
			(var->env[i][len] == '=' || var->env[i][len] == '\0'))
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

void	modify_env_var(t_var *var, char *var_name, char *new_content)
{
	char	*new_var;

	new_var = memlist_add(&var->memlist, ft_strjoin(var_name, new_content));
	if (!new_var)
		ms_exit(var, ms_perror("", "malloc fail()", "", errno));
	remove_env_var(var, var_name);
	add_env_var(var, new_var);
	memlist_free_ptr(&var->memlist, new_var);
}

void    create_env(t_var *var, char **env)
{
    int i;

	i = 0;
	var->env = NULL;
	while (env && env[i])
	{
		if (ft_strncmp(env[i], "SHLVL=", ft_strlen("SHLVL=")) == 0)
		{
			add_env_var(var, "SHLVL=1");
			i++;
			continue ;
		}
		else
			add_env_var(var, env[i]);
		i++;
	}
}
