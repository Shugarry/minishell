/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_exec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miggarc2 <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 19:02:08 by miggarc2          #+#    #+#             */
/*   Updated: 2025/09/12 19:26:37 by frey-gal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*stripped_cmd(t_var *var, int i)
{
	char	*stripped_cmd;

	stripped_cmd = ft_strrchr(var->cmds[i][0], '/');
	if (!stripped_cmd)
		stripped_cmd = var->cmds[i][0];
	else
		stripped_cmd++;
	return (stripped_cmd);
}

bool	ms_exec_builtins(t_var *var, int i, bool child)
{
	if (!ft_strncmp(var->cmds[i][0], "exit", 5) &&
		(!var->pipe_count || child))
		ms_exit_builtin(var, i);
	else if (!ft_strncmp(stripped_cmd(var, i), "cd", 3))
		ms_cd(var, var->cmds[i]);
	else if (!ft_strncmp(stripped_cmd(var, i), "echo", 5) && child)
		ms_echo(var->cmds[i]);
	else if (!ft_strncmp(stripped_cmd(var, i), "pwd", 4) && child)
		ms_pwd(var);
	else if (!ft_strncmp(stripped_cmd(var, i), "env", 4) && child)
		ms_env(var, var->cmds[i]);
	else if (!ft_strncmp(stripped_cmd(var, i), "unset", 6))
		ms_unset(var, var->cmds[i]);
	else if (!ft_strncmp(stripped_cmd(var, i), "export", 7) && var->cmds[i][1])
		ms_export(var, var->cmds[i]);
	else if (!ft_strncmp(stripped_cmd(var, i), "export", 7) && child)
		ms_export(var, var->cmds[i]);
	else
		return (0);
	return (1);
}

void	ft_exec_child(t_var *var, int i, int pipes)
{
	ms_open_fds(var, i);
	if (i < pipes)
		close(var->pipes[2 * i]);
	if (i > 0 && dup2(var->pipes[2 * i - 2], STDIN_FILENO) < 0)
		ms_exit(var, 1);
	if (var->fd_in && dup2(var->fd_in, STDIN_FILENO) < 0)
		ms_exit(var, 1);
	if (i < pipes && dup2(var->pipes[2 * i + 1], STDOUT_FILENO) < 0)
		ms_exit(var, 1);
	if (var->fd_out && dup2(var->fd_out, STDOUT_FILENO) < 0)
		ms_exit(var, 1);
	else if (var->cmds[i][0] && !ms_exec_builtins(var, i, 1)
			&& execve(var->cmds[i][0], var->cmds[i], var->env))
		ms_perror(var->cmds[i][0], ": ", strerror(errno), errno);
	else
		ms_exit(var, -1);
	ms_exit(var, 127);
}

static int	ms_pipex_helper(t_var *var, int i, bool *is_forked, pid_t *child)
{
	if (i < var->pipe_count && pipe(&var->pipes[2 * i]) < 0)
		return (ms_perror("", strerror(errno), "", errno), errno);
	if (var->cmds[i][0])
	{
		if (!ms_exec_builtins(var, i, 0))
		{
			*is_forked = true;
			signal(SIGINT, ms_signal_handle_child);
			signal(SIGQUIT, ms_signal_handle_child);
			*child = fork();
			if (*child < 0)
				return (ms_perror("", strerror(errno), "", errno), errno);
			else if (*child == 0)
				ft_exec_child(var, i, var->pipe_count);
		}
	}
	if (i < var->pipe_count)
		close(var->pipes[2 * i + 1]);
	return (0);
}

int	ms_pipex(t_var *var)
{
	int		i;
	int		status;
	pid_t	child;
	bool	is_forked;
	int		helper_ret;

	i = -1;
	child = -1;
	status = 0;
	is_forked = false;
	while (var->cmds[++i])
	{
		helper_ret = ms_pipex_helper(var, i, &is_forked, &child);
		if (helper_ret)
			return (helper_ret);
	}
	while (i-- > 0)
	{
		if (is_forked && waitpid(-1, &status, 0) == child && WIFEXITED(status))
			var->exit_code = WEXITSTATUS(status);
		if (i > 0)
			close(var->pipes[2 * (i - 1)]);
	}
	return (var->exit_code);
}
