/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_env_init.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frey-gal <frey-gal@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 12:11:29 by frey-gal          #+#    #+#             */
/*   Updated: 2025/07/10 21:20:34 by frey-gal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

static bool	validate_shlvl(char *shlvl)
{
	int		i;

	i = 0;
	if (!shlvl[i])
		return (false);
	if (shlvl[i] == '-' || shlvl[i] == '+')
		i++;
	while (shlvl[i] == '0')
		i++;
	if (ft_strlen(shlvl + i) > 4)
		return (false);
	while (shlvl[i])
		if (!ft_isdigit(shlvl[i++]))
			return (false);
	return (true);
}

void	add_shlvl(t_var *var, char *shlvl)
{
	char	*tmp;
	char	*lvlstr;
	int		lvl;

	if (validate_shlvl(shlvl) == false)
		return (add_env_var(var, "SHLVL=1"));
	lvl = ft_atoi(shlvl);
	if (lvl < 0)
		return (add_env_var(var, "SHLVL=0"));
	lvlstr = memlist_add(var, ft_itoa(lvl + 1));
	if (lvl + 1 > 1000)
	{
		ms_perror("minishell: warning: shell level ",
			lvlstr, "too high, resetting to 1\n", 0);
		memlist_free_ptr(var, lvlstr);
		return (add_env_var(var, "SHLVL=1"));
	}
	tmp = memlist_add(var, ft_strjoin("SHLVL=", lvlstr));
	add_env_var(var, tmp);
	memlist_free_ptr(var, lvlstr);
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
