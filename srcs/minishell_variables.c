/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_variables.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frey-gal <frey-gal@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 12:11:29 by frey-gal          #+#    #+#             */
/*   Updated: 2025/06/26 01:14:27 by frey-gal         ###   ########.fr       */
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
		if (ft_strncmp(var_name, var->env[i], len) == 0
			&& (var->env[i][len] == '=' || var->env[i][len] == '\0'))
		{
			i++;
			continue ;
		}
		new_varlist[j] = memlist_add(var, ft_strdup(var->env[i]));
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

void	modify_env_var(t_var *var, char *var_name, char *new_content)
{
	char	*tmp;
	char	*new_var;

	if (new_content == NULL)
	{
		remove_env_var(var, var_name);
		add_env_var(var, var_name);
		return ;
	}
	tmp = memlist_add(var, ft_strjoin(var_name, "="));
	new_var = memlist_add(var, ft_strjoin(tmp, new_content));
	remove_env_var(var, var_name);
	add_env_var(var, new_var);
	memlist_free_ptr(var, new_var);
}

void	add_shlvl(t_var *var, char *shlvl)
{
	char	*tmp;
	char	*level;
	int		lvl;
	int		i;

	while (*shlvl == '0')
		shlvl++;
	if (!*shlvl || strlen(shlvl) > 5)
		return (add_env_var(var, "SHLVL=1"));
	i = 0;
	while (shlvl[i])
	{
		if (!ft_isdigit(shlvl[i]))
			return (add_env_var(var, "SHLVL=1"));
		i++;
	}
	lvl = ft_atoi(shlvl);
	if (lvl < 0)
		return (add_env_var(var, "SHLVL=0"));
	if (lvl + 1 > 1000)
	{
		printf("minishell: warning: shell level %d too high, \
			resetting to 1\n", lvl + 1);
		return (add_env_var(var, "SHLVL=1"));
	}
	level = ft_itoa(lvl + 1);
	tmp = memlist_add(var, ft_strjoin("SHLVL=", level));
	free(level);
	add_env_var(var, tmp);
	memlist_free_ptr(var, tmp);
}

void	create_env(t_var *var, char **env)
{
	int		i;
	bool	shlvl;
	char	*tmp;

	i = 0;
	shlvl = false;
	var->env = NULL;
	while (env && env[i])
	{
		if (ft_strncmp(env[i], "SHLVL=", ft_strlen("SHLVL=")) == 0)
		{
			shlvl = true;
			add_shlvl(var, ft_strchr(env[i], '=') + 1);
		}
		else
			add_env_var(var, env[i]);
		i++;
	}
	if (!shlvl)
		add_env_var(var, "SHLVL=1");
	tmp = getcwd_plus(var);
	if (!get_env_var(var, "PWD") && tmp)
		modify_env_var(var, "PWD", tmp);
	memlist_free_ptr(var, tmp);
}
