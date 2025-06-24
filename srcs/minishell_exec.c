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

#include "minishell.h"

_Bool	ms_exec_builtins(t_var *var, int i)
{
	char	*stripped_cmd;

	stripped_cmd = ft_strrchr(var->cmds[i][0], '/');
	if (!stripped_cmd)
		stripped_cmd = var->cmds[i][0];
	else
		stripped_cmd++;
	if (ft_strncmp(stripped_cmd, "echo", 5) == 0)
		ms_echo(var->cmds[i]);
	else if (ft_strncmp(stripped_cmd, "cd", 3) == 0)
		ms_cd(var, var->cmds[i]);
	else if (ft_strncmp(stripped_cmd, "pwd", 4) == 0)
		ms_pwd(var);
	else if (ft_strncmp(stripped_cmd, "export", 7) == 0)
		ms_export(var, var->cmds[i]);
	else if (ft_strncmp(stripped_cmd, "unset", 6) == 0)
		ms_unset(var, var->cmds[i]);
	else if (ft_strncmp(stripped_cmd, "env", 4) == 0)
		ms_env(var);
	else
		return (0);
	return (1);
}

void	ft_exec_child(t_var *var, int i, int pipes)
{
	ms_redirect_cmds(var, i);
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
	if (var->cmds[i][0] && !ms_exec_builtins(var, i) && \
		execve(var->cmds[i][0], var->cmds[i], var->env))
		ms_perror(var->cmds[i][0], strerror(errno), "", errno);
	else
		var->exit_code = 0;
	ms_exit(var, -1);
}

int	ms_pipex(t_var *var)
{
	int		i;
	int		status;
	pid_t	child;

	i = -1;
	child = -1;
	status = 0;
	while (var->cmds[++i])
	{
		if (i < var->pipe_count && pipe(&var->pipes[2 * i]) < 0)
			return (ms_perror("", strerror(errno), "", errno), errno);
		if (var->cmds[i][0])
		{
			//Pend separete exit function and fix non numeric second argument
			if (ft_strncmp(var->cmds[0][0], "exit", 5) == 0)
			{
				if (!var->cmds[0][1])
					ms_exit(var, 0);
				else if (var->cmds[0][1] && !var->cmds[0][2])
					ms_exit(var, ft_atoi(var->cmds[i][1]));
				else
					ms_perror("", "exit: ", "too may arguments", 127);
				return (0);
			}
			signal(SIGINT, ms_signal_handle_child);
			signal(SIGQUIT, ms_signal_handle_child);
			child = fork();
			if (child < 0)
				return (ms_perror("", strerror(errno), "", errno), errno);
			else if (child == 0)
				ft_exec_child(var, i, var->pipe_count);
		}
		if (i < var->pipe_count)
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

char	**ms_cmd_trim(char **cmd, int pos)
{
	int		size;
	int		i;
	int		j;
	char	**new_cmd;

	size = 0;
	while (cmd[size])
		size++;
	new_cmd = (char **)ft_calloc(size - 1, sizeof(char *));
	if (!new_cmd)
	{
		ms_perror("", strerror(errno), "", errno);
		return (NULL);
	}
	i = 0;
	j = 0;
	while (j < size)
	{
		if (j == pos)
		{
			free (cmd[j++]);
			free (cmd[j++]);
		}
		new_cmd[i++] = cmd[j++];
	}
	free(cmd);
	return (new_cmd);
}

int	ms_redirect_cmds(t_var *var, int i)
{
	int			j;
	char		*hd_no;
	char		*hd_name;

	j = 0;
	while (var->cmds[i][j])
	{
		if (!ft_strncmp(var->cmds[i][j], ">", 1))
		{
			if (!var->cmds[i][j + 1])
				ms_perror("", "syntax error near unexpected token `'", "'", 2);
			if (var->fd_out > 0)
				close(var->fd_out);
			if (!ft_strncmp(var->cmds[i][j], ">", 2))
				var->fd_out = open(var->cmds[i][j + 1],
						O_WRONLY | O_CREAT | O_TRUNC, 0644);
			else if (!ft_strncmp(var->cmds[i][j], ">>", 3))
				var->fd_out = open(var->cmds[i][j + 1],
						O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (var->fd_out < 0)
				ms_perror(strerror(errno), ": ", var->cmds[i][j + 1], 1);
			var->cmds[i] = ms_cmd_trim(var->cmds[i], j);
		}
		else if (!ft_strncmp(var->cmds[i][j], "<", 1))
		{
			if (!var->cmds[i][j + 1])
				ms_perror("", "syntax error near unexpected token `'", "'", 2);
			if (var->fd_in > 0)
				close(var->fd_in);
			if (!ft_strncmp(var->cmds[i][j], "<", 2))
				var->fd_in = open(var->cmds[i][j + 1], O_RDONLY);
			else if (!ft_strncmp(var->cmds[i][j], "<<", 3))
			{
				hd_no = ft_itoa(var->hd_int++);
				hd_name = ft_strjoin(".here_doc_", hd_no);
				if (!hd_no || !hd_name)
					ms_perror("", strerror(errno), "\n", errno);
				free(hd_no);
				var->fd_in = open(hd_name, O_RDONLY);
				free(hd_name);
			}
			if (var->fd_in < 0)
				ms_perror(strerror(errno), ": ", var->cmds[i][j + 1], 1);
			var->cmds[i] = ms_cmd_trim(var->cmds[i], j);
		}
		else
			j++;
	}
	ms_cmd_resolve(var, i);
	return (var->exit_code);
}
