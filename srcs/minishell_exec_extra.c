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

char	**ms_alloc_cmd(char **cmd, int *size)
{
	char	**new_cmd;

	while (cmd[*size])
		(*size)++;
	new_cmd = (char **)ft_calloc(*size, sizeof(char *));
	if (!new_cmd)
	{
		ms_perror("", strerror(errno), "", errno);
		return (NULL);
	}
	return (new_cmd);
}

char	**ms_cmd_trim(char **cmd, int pos)
{
	int		size;
	int		i;
	int		j;
	char	**new_cmd;

	size = 0;
	new_cmd = ms_alloc_cmd(cmd, &size);
	if (!new_cmd)
		return (NULL);
	i = 0;
	j = 0;
	while (j <= size)
	{
		if (j == pos)
		{
			free (cmd[j++]);
			if (cmd[j])
				free (cmd[j++]);
		}
		new_cmd[i++] = cmd[j++];
	}
	free(cmd);
	return (new_cmd);
}

int	ms_open_fds(t_var *var, int i)
{
	int			j;
	char		*hd_no;
	char		*hd_name;

	j = 0;
	while (var->cmds[i][j])
	{
		if (!ft_strncmp(var->cmds[i][j], ">", 2))
		{
			if (var->fd_out > 0)
				close(var->fd_out);
			if (!ft_strncmp(var->cmds[i][j], ">", 2) && var->cmds[i][j + 1])
				var->fd_out = open(var->cmds[i][j + 1],
						O_WRONLY | O_CREAT | O_TRUNC, 0644);
			else if (!ft_strncmp(var->cmds[i][j], ">>", 3) && var->cmds[i][j + 1])
				var->fd_out = open(var->cmds[i][j + 1],
						O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (var->fd_out < 0)
				ms_perror(strerror(errno), ": ", var->cmds[i][j + 1], 1);
			var->cmds[i] = ms_cmd_trim(var->cmds[i], j);
		}
		else if (!ft_strncmp(var->cmds[i][j], "<", 2))
		{
			if (var->fd_in > 0)
				close(var->fd_in);
			if (!ft_strncmp(var->cmds[i][j], "<", 2) && var->cmds[i][j + 1])
				var->fd_in = open(var->cmds[i][j + 1], O_RDONLY);
			else if (!ft_strncmp(var->cmds[i][j], "<<", 3) && var->cmds[i][j + 1])
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
	return (0);
}
