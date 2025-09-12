/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_heredoc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frey-gal <frey-gal@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 19:40:34 by frey-gal          #+#    #+#             */
/*   Updated: 2025/09/12 19:40:35 by frey-gal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
	while (j <= size)
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

static void	opfds_helper_a(t_var *var, int i, int j)
{
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

static void	opfds_helper_b(t_var *var, int i, int j, char **hd_vars)
{
	if (var->fd_in > 0)
		close(var->fd_in);
	if (!ft_strncmp(var->cmds[i][j], "<", 2))
		var->fd_in = open(var->cmds[i][j + 1], O_RDONLY);
	else if (!ft_strncmp(var->cmds[i][j], "<<", 3))
	{
		hd_vars[HD_NO] = ft_itoa(var->hd_int++);
		hd_vars[HD_NAME] = ft_strjoin(".here_doc_", hd_vars[HD_NO]);
		if (!hd_vars[HD_NO] || !hd_vars[HD_NAME])
			ms_perror("", strerror(errno), "\n", errno);
		free(hd_vars[HD_NO]);
		var->fd_in = open(hd_vars[HD_NAME], O_RDONLY);
		free(hd_vars[HD_NAME]);
	}
	if (var->fd_in < 0)
		ms_perror(strerror(errno), ": ", var->cmds[i][j + 1], 1);
	var->cmds[i] = ms_cmd_trim(var->cmds[i], j);
}

int	ms_open_fds(t_var *var, int i)
{
	int			j;
	char		*hd_vars[2];

	j = 0;
	while (var->cmds[i][j])
	{
		if (!ft_strncmp(var->cmds[i][j], ">", 1) && var->cmds[i][j + 1]
			&& ft_strlen(var->cmds[i][j]) <= 2)
			opfds_helper_a(var, i, j);
		else if (!ft_strncmp(var->cmds[i][j], "<", 1) && var->cmds[i][j + 1]
			&& ft_strlen(var->cmds[i][j]) <= 2)
			opfds_helper_b(var, i, j, hd_vars);
		else
			j++;
	}
	ms_cmd_resolve(var, i);
	return (0);
}
