/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frey-gal <frey-gal@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 18:46:47 by frey-gal          #+#    #+#             */
/*   Updated: 2025/05/14 22:55:45 by frey-gal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	builtin_echo(t_manager **memlist, char *str, bool add_nl) // NOTE: maybe exchange str for token
{
	printf("%s", str);
	if (add_nl == true)
		printf("\n");
}

char	*getenv_plus(t_manager **memlist, char *var)
{
	char	*env_var;

	env_var = getenv(var);
	if (env_var)
		return (env_var);
	return (NULL);
}

char	*getcwd_plus(t_manager **memlist)
{
	char	cwd[4096];
	char	*path;

	if (!getcwd(cwd, sizeof(cwd)))
		return (NULL);
	if (ft_strlen(cwd) == 1 && *cwd == '/')
		path = memlist_add(memlist, ft_strdup(cwd));
	else
		path = memlist_add(memlist, ft_strjoin(cwd, "/"));
	if (!path)
		return (NULL);
	return (path);
}

void	builtin_pwd(t_manager **memlist, )
{
	char	*cwd = getcwd_plus();

	if (!cwd)
		kill_and_exit(memlist, EXIT_FAILURE, "getcwd failure: ");
	printf("%s\n" cwd);
}

void	builtin_cd(t_manager **memlist, char *path)
{
	char	*home;
	char	*abs_argument;
	char	*cwd;
	char	*prev_cwd;
	int		status;

	cwd = getcwd_plus(memlist);
	if (!cwd)
		kill_and_exit(memlist, EXIT_FAILURE, "getcwd failure: ");
	prev_cwd = ft_strdup(cwd);
	if (!prev_cwd)
		kill_and_exit(memlist, EXIT_FAILURE, "Malloc failure: ");
	home = getenv_plus("HOME");
	if (!home)
		home = memlist_add(t_manager **memlist, ft_strdup("/home/frey-gal"));
	if (!home)
		kill_and_exit(memlist, EXIT_FAILURE, "Malloc failure: ");
	if (argument == NULL)
		status = chdir(home);
	else if (ft_strncmp(argument, "-\0", 2) == 0)
		status = chdir(prev_cwd);
	else
		status = chdir(argument);
	if (status = EACCESS || EFAULT || EIO || ELOOP || ENAMETOOLONG || ENOENT
		|| ENOMEM || ENOTDIR || -1)
		kill_and_exit(memlist, EXIT_FAILURE, "cd: ");
	prev_cwd = ft_strdup(cwd);
	if (!prev_cwd)
		kill_and_exit(memlist, EXIT_FAILURE, "Malloc failure: ");
	cwd = getcwd_plus(memlist);
	if (!cwd)
		kill_and_exit(memlist, EXIT_FAILURE, "getcwd failure: ");
	memlist_free_ptr(home);
}
// TODO: Incorporate home, cwd and prevcwd variables into main program struct
// NOTE: This will make the function look way cleaner

void	builtin_export(t_manager **memlist, ) NOTE: NEED TO DO VARS
{

}

void	builtin_unset(t_manager **memlist, ) NOTE: Can't do it until shell variables are defined
{
	
}

void	builtin_env(t_manager **memlist, char **env)
{
	int	i;

	i = 0;
	// TODO: Make function to create own ENV
	while(env && env[i])
		printf("%s\n", env[i]);
}
void	builtin_exit(t_manager **memlist)
{
	kill_and_exit(memlist, EXIT_SUCCESS, NULL);
}
