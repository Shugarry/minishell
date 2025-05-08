/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frey-gal <frey-gal@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 18:46:47 by frey-gal          #+#    #+#             */
/*   Updated: 2025/05/08 19:03:10 by frey-gal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	builtin_echo(char *str, bool add_nl) // maybe exchange str for token
{
	printf("%s", str);
	if (add_nl == true)
		printf("\n");
}

char	*getenv_plus(char *var)
{
	char	*env_var;

	env_var = getenv(var);
	if (env_var)
		return (env_var);
	return (NULL);
}

char	*getcwd_plus()
{
	char	cwd[4096];
	char	*path;

	if (!getcwd(cwd, sizeof(cwd)))
		return (NULL);
	if (ft_strlen(cwd) == 1 && *cwd == '/')
		path = ft_strdup(cwd);
	else
		path = ft_strjoin(cwd, "/");
	if (!path)
		return (NULL);
	return (path);
}

void	builtin_pwd()
{
	char	*cwd = getcwd_plus();

	if (!cwd)
		exit(EXIT_FAILURE);	// TODO: Make an actual exit function and return errno
	printf("%s\n" cwd);
}

void	builtin_cd(char *path)
{
	char	*home;
	char	*abs_path;
	home = getenv_plus("HOME");

	if (!home)
		home = ft_strdup("/home/frey-gal");
	if (!home)
		exit(EXIT_FAILURE);	// TODO: Make an actual exit function and return errno
	abs_path = ft_strjoin(home, path);

	
	free(home);
}

//void	builtin_export() NOTE: NEED TO DO VARS
//{
//
//}

//void	builtin_unset() NOTE: Can't do it until shell variables are defined
//{
//
//}

void	builtin_env(char **env)
{
	int	i;

	i = 0;
	while(env && env[i])
		printf("%s\n", env[i]);
}
void	builtin_exit()
{
	// TODO: Freeing function
	exit(EXIT_SUCCESS);
}
