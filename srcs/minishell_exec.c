/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   minishell_exec.c								   :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: miggarc2 <marvin@42.fr>					+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2025/02/06 19:02:08 by miggarc2		  #+#	#+#			 */
/*   Updated: 2025/06/23 07:41:43 by frey-gal		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "../minishell.h"

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
	ms_exit(var, g_signal_code);
}

void	pid_waiter(t_var *var, pid_t child, int i)
{
	int	status;

	status = 0;
	while (i-- > 0)
	{
		if (waitpid(-1, &status, 0) == child && WIFEXITED(status))
			g_signal_code = WEXITSTATUS(status);
		if (i > 0)
			close(var->pipes[2 * (i - 1)]);
	}
}

int	ms_pipex(t_var *var)
{
	int		i;
	pid_t	child;

	i = -1;
	while (var->cmds[++i])
	{
		if (i < var->pipe_count && pipe(&var->pipes[2 * i]) < 0)
			return (ms_perror("", strerror(errno), "", errno), errno);
		if (var->cmds[i][0] && !ms_exec_builtins(var, i, 0))
		{
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
	pid_waiter(var, child, i);
	return (g_signal_code);
}
