/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_exec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miggarc2 <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 19:02:08 by miggarc2          #+#    #+#             */
/*   Updated: 2025/06/23 07:41:43 by frey-gal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	ms_exec_builtins(t_var *var, int i, bool child)
{
	char	*stripped_cmd;

	stripped_cmd = ft_strrchr(var->cmds[i][0], '/');
	if (!stripped_cmd)
		stripped_cmd = var->cmds[i][0];
	else
		stripped_cmd++;
	if (!ft_strncmp(var->cmds[0][0], "exit", 5))
		ms_exit_builtin(var);
	else if (!ft_strncmp(stripped_cmd, "cd", 3))
		ms_cd(var, var->cmds[i]);
	else if (!ft_strncmp(stripped_cmd, "echo", 5) && child)
		ms_echo(var->cmds[i]);
	else if (!ft_strncmp(stripped_cmd, "pwd", 4) && child)
		ms_pwd(var);
	else if (!ft_strncmp(stripped_cmd, "env", 4) && child)
		ms_env(var, var->cmds[i]);
	else if (!ft_strncmp(stripped_cmd, "unset", 6))
		ms_unset(var, var->cmds[i]);
	else if (!ft_strncmp(stripped_cmd, "export", 7) && var->cmds[i][1])
		ms_export(var, var->cmds[i]);
	else if (!ft_strncmp(stripped_cmd, "export", 7) && child)
		ms_export(var, var->cmds[i]);
	else
		return (0);
	return (1);
}
