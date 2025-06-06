/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_exec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miggarc2 <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 19:02:08 by miggarc2          #+#    #+#             */
/*   Updated: 2025/06/06 04:44:30 by frey-gal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_exec_child(t_var *var, int i, int end)
{
	(void)end;
	if (i < end)
		close(var->pipes[2 * i]);
/*	if (i == 0 && dup2(var->fd_in, STDIN_FILENO) < 0)
		ms_exit(var, 1);
	else */if (i > 0 && dup2(var->pipes[2 * i - 2], STDIN_FILENO) < 0)
		ms_exit(var, 1);
	if (i < end && dup2(var->pipes[2 * i + 1], STDOUT_FILENO) < 0)
		ms_exit(var, 1);
//	else if (i == end && dup2(var->fd_out, STDOUT_FILENO) < 0)
//		ms_exit(var, 1);
	if (var->cmds[i][0] == NULL)
		ms_exit(var, ms_perror("", "permission denied: ", "", 126));
	
	execve(var->cmds[i][0], var->cmds[i], var->env);
	ms_exit(var, ms_perror(var->cmds[i][0], ": command not found", "", 127));
}

_Bool	ms_exec_builtins(t_var *var, int i)
{
	if (ft_strncmp(var->cmds[i][0], "echo", 5) == 0
		|| ft_strncmp(var->cmds[i][0], "/usr/bin/echo", 5) == 0)
		ft_echo(var->cmds[i]);
	else if (ft_strncmp(var->cmds[i][0], "cd", 3) == 0)
		ft_cd(var, var->cmds[i]);
	else if (ft_strncmp(var->cmds[i][0], "pwd", 4) == 0)
	{
	printf("hello");
		ft_pwd(var);
}
	/*
	else if (ft_strncmp(var->cmds[i][0], "export", 7) == 0)
		ft_export(var, var->cmds[i]);
	else if (ft_strncmp(var->cmds[i][0], "unset", 6) == 0)
		ft_unset(var, var->cmds[i]);
	else if (ft_strncmp(var->cmds[i][0], "env", 4) == 0)
		ft_env(var);
	else */
	if (ft_strncmp(var->cmds[i][0], "exit", 5) == 0)
	{
		if (var->cmds[i][1])
			ms_exit(var, ft_atoi(var->cmds[i][1]));
		else
			ms_exit(var, 0);
	}
	else if (ft_strncmp(var->cmds[i][0], "$?", 3) == 0)
		ft_printf("%d\n", var->exit_code);
	else
		return (0);
	var->exit_code = 0;
	return (1);
}

int	ms_pipex(t_var *var, int end)
{
	int		i;
	int		status;
	pid_t	child;

	i = -1;
	while (var->cmds[++i])
	{
		if (i < end && pipe(&var->pipes[2 * i]) < 0)
			ms_exit(var, ms_perror("", strerror(errno), "", errno));
		if (var->cmds[i][0] && !ms_exec_builtins(var, i))
		{
			signal(SIGINT, ms_signal_handle_child);
			signal(SIGQUIT, ms_signal_handle_child);
			child = fork();
			if (child < 0)
				ms_exit(var, ms_perror("", strerror(errno), "", errno));
			else if (child == 0)
				ft_exec_child(var, i, end);
		}
		if (i < end)
			close(var->pipes[2 * i + 1]);
	}
	while (i-- > 0)
	{
		if (waitpid(-1, &status, 0) == child && WIFEXITED(status))
			var->exit_code = WEXITSTATUS(status);
		if (i > 0)
			close(var->pipes[2 * (i - 1)]);
	}
	return (var->exit_code);
}
