/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miggarc2 <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 19:02:08 by miggarc2          #+#    #+#             */
/*   Updated: 2025/05/07 22:34:38 by miggarc2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_perror(char *err1, char *err2, char *err3, int err_no)
{
	ft_putstr_fd(err1, STDERR_FILENO);
	ft_putstr_fd(err2, STDERR_FILENO);
	ft_putendl_fd(err3, STDERR_FILENO);
	return (err_no);
}

void	ms_clean(char **var_ptr)
{
	int	i;

	if (var_ptr)
	{
		i = 0;
		while (var_ptr[i])
		{
			free(var_ptr[i]);
			i++;
		}
		free(var_ptr);
	}
}

void	ms_free_ptrs(t_var *var)
{
	int	i;

	if (var->pipes)
		free(var->pipes);
	if (var->tokens)
		free(var->tokens);
	if (var->cmds)
	{
		i = 0;
		while (var->cmds[i])
			ms_clean(var->cmds[i++]);
		free(var->cmds);
	}
	if (var->cmd_splitters)
		ms_clean(var->cmd_splitters);
	if (var->line)
		free(var->line);
	var->pipes = NULL;
	var->tokens = NULL;
	var->cmds = NULL;
	var->cmd_splitters = NULL;
	var->line = NULL;
}

void	ms_exit(t_var *var, int exit_code)
{
	close(STDIN_FILENO);
	if (access(".here_doc", F_OK) == 0)
		unlink(".here_doc");
	if (var->fd_in > 0)
		close(var->fd_in);
	if (var->fd_out > 0)
		close(var->fd_out);
	ms_free_ptrs(var);
	if (var->paths)
		ms_clean(var->paths);
	if (!exit_code)
		ft_putendl_fd("exit", STDOUT_FILENO);
	rl_clear_history();
	memlist_free_all(&var->memlist);
	exit(exit_code);
}
