/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_builtins.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frey-gal <frey-gal@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 18:46:47 by frey-gal          #+#    #+#             */
/*   Updated: 2025/06/23 07:41:25 by frey-gal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ms_echo(char **tokens)
{
	bool	add_nl;
	int		i;
	int		j;

	i = 1;
	add_nl = true;
	while (tokens && tokens[i] != NULL && ft_strncmp(tokens[i], "-n", 2) == 0)
	{
		j = 1;
		while (tokens[i][j] == 'n')
			j++;
		if (tokens[i][j] == '\0')
			add_nl = false;
		else
			printf("%s", tokens[i]);
		if (tokens[i + 1])
			printf(" ");
		i++;
	}
	while (tokens && tokens[i] != NULL)
	{
		printf("%s", tokens[i]);
		if (tokens[i + 1])
			printf(" ");
		i++;
	}
	if (add_nl == true)
		printf("\n");
}

char	*getcwd_plus(t_var *var)
{
	char	cwd[4096];
	char	*path;

	if (!getcwd(cwd, sizeof(cwd)))
		return (NULL);
	if (ft_strlen(cwd) == 1 && *cwd == '/')
		path = memlist_add(&var->memlist, ft_strdup(cwd));
	else
		path = memlist_add(&var->memlist, ft_strjoin(cwd, "/"));
	if (!path)
		return (NULL);
	return (path);
}

int		ms_pwd(t_var *var)
{
	char	*cwd;
	
	cwd = getcwd_plus(var);
	if (!cwd)
		return (0);
	printf("%s\n", cwd);
	memlist_free_ptr(&var->memlist, cwd);
	return (1);
}

int	bad_status(int status)
{
	return (status == EACCES || status == EFAULT || status == EIO
			|| status == ELOOP || status == ENAMETOOLONG || status == ENOENT
			|| status == ENOMEM || status == ENOTDIR || status == -1);
}

int	ms_cd(t_var *var, char **tokens)
{
	char	*home;
	char	*pwd;
	char	*tmp;

	if (!tokens[1] || (tokens[1] && ft_strcmp(tokens[1], "--") == 0))
	{
		home = get_env_var(var, "HOME");
		if (!home)
			return (ms_perror("minishell: ", "cd: ", "HOME not set", 1));
		if (bad_status(chdir(home)))
			return (ms_perror("", strerror(errno), "", errno));
		pwd = get_env_var(var, "PWD");
		modify_env_var(var, "OLDPWD", pwd);
		modify_env_var(var, "PWD", home);
		memlist_free_ptr(&var->memlist, home);
		memlist_free_ptr(&var->memlist, pwd);
		return (1);
	}
	else if (tokens[2] != NULL)
		return (ms_perror("minishell: ", "cd: ", "too many arguments", 1));
	else if (ft_strcmp(tokens[1], "-") == 0)
	{
		if (!get_env_var(var, "OLDPWD"))
			return (ms_perror("minishell: ", "cd: ", "OLDPWD not set", 1));
		if (bad_status(chdir(get_env_var(var, "OLDPWD"))))
			return (ms_perror("minishell:", "cd:", strerror(errno), errno));
		tmp = memlist_add(&var->memlist, ft_strdup(get_env_var(var, "OLDPWD")));
		if (!tmp)
			ms_exit(var, ms_perror("", strerror(errno), "", errno));
		modify_env_var(var, "OLDPWD", get_env_var(var, "PWD"));
		modify_env_var(var, "PWD", tmp);
		memlist_free_ptr(&var->memlist, tmp);
}
	else
	{
		if (bad_status(chdir(tokens[1])))
			return (ms_perror("minishell:", "cd:", strerror(errno), errno));
		pwd = get_env_var(var, "PWD");
		if (!pwd)
			ms_exit(var, ms_perror("", strerror(errno), "", errno));
		modify_env_var(var, "OLDPWD", pwd);
		modify_env_var(var, "PWD", tokens[1]);
		memlist_free_ptr(&var->memlist, pwd);
	}
	return (1);
}

void	ms_export(t_var *var, char **tokens)
{
	int		i;
	int		j;
	char	*variable;
	char	*content;

	i = 1;
	if (!tokens[i])
	{
		j = 0;
		while(var->varlist[j])
		{
			variable = (char *)memlist_add(&var->memlist, ft_strdup(var->varlist[j]));
			content = ft_strchr(variable, '=');
			if (content)
			{
				content[0] = '\0';
				content++;
				printf("declare -x %s=\"%s\"\n", variable, content);
			}
			else if (!content)
				printf("declare -x %s\n", variable);
			j++;
		}
	}
	while (tokens[i])
	{
		variable = memlist_add(&var->memlist, ft_strdup(tokens[i]));
		if (!variable)
			ms_exit(var, ms_perror("", strerror(errno), "", errno));
		i++;
	}
}

void	ms_unset(t_var *var, char **tokens)
{
	int	i;

	i = 1;
	while (tokens[i])
	{
		remove_env_var(var, tokens[i]);
		i++;
	}
}

void	ms_env(t_var *var)
{
	int	i;

	i = 0;
	while(var->varlist[i] != NULL)
	{
		printf("%s\n", var->varlist[i]);
		i++;
	}
}
