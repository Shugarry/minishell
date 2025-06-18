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

void	ft_exec_child(t_var *var, int i, int pipes)
{
	if (i < pipes)
		close(var->pipes[2 * i]);
	if (var->fd_in && dup2(var->fd_in, STDIN_FILENO) < 0)
		ms_exit(var, 1);
	if (i > 0 && dup2(var->pipes[2 * i - 2], STDIN_FILENO) < 0)
		ms_exit(var, 1);
	if (var->fd_out && dup2(var->fd_out, STDOUT_FILENO) < 0)
		ms_exit(var, 1);
	if (i < pipes && dup2(var->pipes[2 * i + 1], STDOUT_FILENO) < 0)
		ms_exit(var, 1);
	if (var->cmds[i][0] == NULL)
		ms_exit(var, ms_perror("", "permission denied: ", "", 126));
	
	execve(var->cmds[i][0], var->cmds[i], var->env);
	ms_exit(var, ms_perror(var->cmds[i][0], ": command not found", "", 127));
}

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
			ms_exit(var, ms_perror("", strerror(errno), "", errno));
		if (var->cmds[i][0])
		{
			if (ft_strncmp(var->cmds[0][0], "exit", 5) == 0)
			{
				if (var->cmds[0][1])
					ms_exit(var, ft_atoi(var->cmds[i][1]));
				else
					ms_exit(var, 0);
			}
			signal(SIGINT, ms_signal_handle_child);
			signal(SIGQUIT, ms_signal_handle_child);
			child = fork();
			if (child < 0)
				ms_exit(var, ms_perror("", strerror(errno), "", errno));
			else if (child == 0)
			{
				if (!ms_exec_builtins(var, i))
					ft_exec_child(var, i, var->pipe_count);
				else
				{
					var->exit_code = 0;
					ms_exit(var, -1);
				}
			}
			// Pend redirect builtins to pipes and improve their exit
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

void	ms_open_heredoc(t_var *var, char *limit, size_t limit_len)
{
	char	*line;
	int		here_fd;

	here_fd = open(".here_doc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (here_fd < 0)
		ms_exit(var, ms_perror("", strerror(errno), "\n", errno));
	while (1)
	{
		ft_putstr_fd("> ", STDOUT_FILENO);
		line = get_next_line(STDIN_FILENO);
		if (!line)
			break ;
		if (ft_strncmp(line, limit, limit_len) == 0 && line[limit_len] == '\n')
		{
			close(STDIN_FILENO);
			free(line);
			line = get_next_line(STDIN_FILENO);
			break ;
		}
		else
			ft_putstr_fd(line, here_fd);
		free(line);
	}
	close(here_fd);
	var->fd_in = open(".here_doc", O_RDONLY);
}

int	ms_exec_cmds(t_var *var)
{
	int	i;
	int	j;

	i = -1;
	while (var->cmds[++i])
	{
		j = -1;
		while (var->cmds[i][++j])
		{
			if (!ft_strncmp(var->cmds[i][j], ">", 1))
			{
				if (var->fd_out > 0)
					close(var->fd_out);
				if (!ft_strncmp(var->cmds[i][j], ">", 2))
					var->fd_out = open(var->cmds[i][j + 1], \
						O_WRONLY | O_CREAT | O_TRUNC, 0644);
				else
					var->fd_out = open(var->cmds[i][j + 1], \
						O_WRONLY | O_CREAT | O_APPEND, 0644);
				if (var->fd_out < 0)
					ms_perror(strerror(errno), ": ", var->cmds[i][j + 1], 1);
				var->cmds[i][j] = NULL;
				var->cmds[i][j + 1] = NULL;
			}
			else if (!ft_strncmp(var->cmds[i][j], "<", 1))
			{
				if (access(".here_doc", F_OK) == 0)
					unlink(".here_doc");
				if (var->fd_in > 0)
					close(var->fd_in);
				if (!ft_strncmp(var->cmds[i][j], "<", 2))
					var->fd_in = open(var->cmds[i][j + 1], O_RDONLY);
				else
					ms_open_heredoc(var, var->cmds[i][j + 1], ft_strlen(var->cmds[i][j + 1]));
				if (var->fd_in < 0)
					ms_perror(strerror(errno), ": ", var->cmds[i][j + 1], 1);
				var->cmds[i][j] = NULL;
			}
		}
	}
	return (var->exit_code);
}