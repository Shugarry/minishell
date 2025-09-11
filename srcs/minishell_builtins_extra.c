/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_builtins_extra.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frey-gal <frey-gal@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 18:46:47 by frey-gal          #+#    #+#             */
/*   Updated: 2025/07/10 19:38:43 by frey-gal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// NOTE: Because of norminette im forced to do tokens[i++ + 1], separating into
// various functions is not worth the trouble
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
			break ;
		i++;
	}
	while (tokens && tokens[i] != NULL)
	{
		printf("%s", tokens[i]);
		if (tokens[i++ + 1])
			printf(" ");
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
	path = memlist_add(var, ft_strdup(cwd));
	return (path);
}

void	ms_pwd(t_var *var)
{
	if (var->pwd)
		printf("%s\n", var->pwd);
	else if (get_env_var(var, "PWD"))
		printf("%s\n", get_env_var(var, "PWD"));
	else
	{
		var->exit_code = 1;
		ms_perror("minishell: ", "pwd: ", \
			"error retrieving current directory: No such file or directory", 1);
	}
}

void	ms_exit_builtin(t_var *var, int i)
{
	int	k;

	k = 0;
	if (!var->cmds[i][1])
		ms_exit(var, 0);
	else if (var->cmds[i][1] && !var->cmds[i][2])
	{
		while (var->cmds[i][1][k])
		{
			if (!ft_isdigit(var->cmds[i][1][k++]))
			{
				ms_perror("", "exit: ", "numeric argument required", 2);
				return ;
			}
		}
		ms_exit(var, ft_atoi(var->cmds[i][1]));
	}
	else
		ms_perror("", "exit: ", "too many arguments", 127);
}
