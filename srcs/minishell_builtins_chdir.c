/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_builtins_chdir.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frey-gal <frey-gal@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 18:13:47 by frey-gal          #+#    #+#             */
/*   Updated: 2025/07/10 21:26:57 by frey-gal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	bad_status(int status)
{
	return (status == EACCES || status == EFAULT || status == EIO
		|| status == ELOOP || status == ENAMETOOLONG || status == ENOENT
		|| status == ENOMEM || status == ENOTDIR || status == -1);
}

static void	cd_home(t_var *var)
{
	char	*pwd;

	pwd = getcwd_plus(var);
	if (get_env_var(var, "HOME") == NULL)
	{
		ms_perror("minishell: ", "cd: ", "HOME not set", 1);
		var->exit_code = 1;
		return ;
	}
	if (bad_status(chdir(get_env_var(var, "HOME"))))
	{
		ms_perror("minishell: ", "cd: ", strerror(errno), errno);
		//TODO: work around bad status
		return ;
	}
	modify_env_var(var, "OLDPWD", pwd);
	modify_env_var(var, "PWD", get_env_var(var, "HOME"));
	if (get_env_var(var, "HOME"))
	{
		memlist_free_ptr(var, var->pwd);
		var->pwd = memlist_add(var, ft_strdup(get_env_var(var, "HOME")));
	}
	memlist_free_ptr(var, pwd);
	var->exit_code = 0;
}

static void	cd_previous(t_var *var)
{
	char	*tmp;

	if (!get_env_var(var, "OLDPWD"))
	{
		ms_perror("minishell: ", "cd: ", "OLDPWD not set", 1);
		var->exit_code = 1;
		return ;
	}
	if (bad_status(chdir(get_env_var(var, "OLDPWD"))))
	{
		ms_perror("minishell:", "cd:", strerror(errno), errno);
		//TODO BAD STATUS
		return ;
	}
	tmp = memlist_add(var, ft_strdup(get_env_var(var, "OLDPWD")));
	modify_env_var(var, "OLDPWD", get_env_var(var, "PWD"));
	modify_env_var(var, "PWD", tmp);
	if (tmp && tmp[0])
	{
		memlist_free_ptr(var, var->pwd);
		var->pwd = memlist_add(var, ft_strdup(tmp));
	}
	memlist_free_ptr(var, tmp);
	var->exit_code = 0;
}

static void	cd_todir(t_var *var, char **tokens)
{
	char	*tmp;

	tmp = getcwd_plus(var);
	if (bad_status(chdir(tokens[1])))
	{
		// TODO BAD STATUS
		ms_perror("minishell: ", "cd: ", strerror(errno), errno);
		return ;
	}
	modify_env_var(var, "OLDPWD", tmp);
	memlist_free_ptr(var, tmp);
	tmp = getcwd_plus(var);
	modify_env_var(var, "PWD", tmp);
	if (tmp && tmp[0])
	{
		memlist_free_ptr(var, var->pwd);
		var->pwd = memlist_add(var, ft_strdup(tmp));
	}
	memlist_free_ptr(var, tmp);
	var->exit_code = 0;
}

void	ms_cd(t_var *var, char **tokens)
{
	if (!tokens[1] || (tokens[1] && ft_strncmp(tokens[1], "--", 3) == 0))
		cd_home(var);
	else if (tokens[2] != NULL)
		ms_perror("minishell: ", "cd: ", "too many arguments", 1);
	else if (ft_strncmp(tokens[1], "-", 2) == 0)
		cd_previous(var);
	else
		cd_todir(var, tokens);
}
