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

int	ft_perror(char *err1, char *err2, char *err3, int err_no)
{
	ft_putstr_fd(err1, STDERR_FILENO);
	ft_putstr_fd(err2, STDERR_FILENO);
	ft_putendl_fd(err3, STDERR_FILENO);
	return (err_no);
}

void	ft_clean(char **var_ptr)
{
	int	i;

	if (var_ptr)
	{
		i = 0;
		while (var_ptr[i])
			free(var_ptr[i++]);
		free(var_ptr);
	}
}

void	ft_exit(t_var *var, int exit_code)
{
	int	i;

	close(STDIN_FILENO);
	free(var->line);
	if (!exit_code)
		ft_printf("exit\n");
	if (access("here_doc", F_OK) == 0)
		unlink("here_doc");
	if (var->pipes)
		free(var->pipes);
	if (var->fd_in > 0)
		close(var->fd_in);
	if (var->fd_out > 0)
		close(var->fd_out);
	i = 0;
	if (var->cmds)
	{
		while (var->cmds[i])
			ft_clean(var->cmds[i++]);
		free(var->cmds);
	}
	if (var->paths)
		ft_clean(var->paths);
	exit(exit_code);
}
