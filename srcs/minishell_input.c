/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_input.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miggarc2 <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 19:02:08 by miggarc2          #+#    #+#             */
/*   Updated: 2025/05/07 20:37:49 by miggarc2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_open_heredoc(t_var *var, char *limit, size_t limit_len)
{
	char	*line;
	int		here_fd;

	here_fd = open("here_doc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (here_fd < 0)
		ft_exit(var, ft_perror("", strerror(errno), "\n", errno));
	while (1)
	{
//		ft_putstr_fd("pipex heredoc> ", STDOUT_FILENO);
		line = readline("minishell$ "); //get_next_line(STDIN_FILENO);
		if (!line)
			break ;
		if (ft_strncmp(line, limit, limit_len) == 0 /*&& line[limit_len] == '\n'*/)
		{
			close(STDIN_FILENO);
			free(line);
			line = readline("minishell"); //get_next_line(STDIN_FILENO);
			break ;
		}
		else if (*line != '\0')
			add_history(line); //ft_putstr_fd(line, here_fd);
		free(line);
	}
	close(here_fd);
}

char	*ft_cmd_resolve(t_var *var, int i)
{
	int		j;
	char	*tmp;
	char	*cmd;

	j = -1;
	while (var->paths[++j])
	{
		if (var->cmds[i][0] && ft_strncmp(var->cmds[i][0], "/", 1))
		{
			tmp = ft_strjoin(var->paths[j], "/");
			cmd = ft_strjoin(tmp, var->cmds[i][0]);
			free(tmp);
		}
		else
			cmd = ft_strdup(var->cmds[i][0]);
		if (access(cmd, F_OK | X_OK) == 0)
			break ;
		free(cmd);
	}
	if (var->paths[j])
		free(var->cmds[i][0]);
	else
		return (var->cmds[i][0]);
	return (cmd);
}

void	ft_start_args(t_var *var, char **av, int ac)
{
	int	i;

	var->fd_in = open(av[1], O_RDONLY);
	if (var->fd_in < 0)
		ft_perror(strerror(errno), ": ", av[1], 1);
	if (var->hdoc)
		var->fd_out = open(av[ac - 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		var->fd_out = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (var->fd_out < 0)
		ft_perror(strerror(errno), ": ", av[ac - 1], 1);
	var->cmds = (char ***)ft_calloc(ac - 2 - var->hdoc, sizeof(char **));
	if (!var->cmds)
		ft_exit(var, ft_perror("", strerror(errno), "", errno));
	i = -1;
	while (++i <= ac - 4 - var->hdoc)
	{
		var->cmds[i] = ft_split(av[i + 2 + var->hdoc], ' ');
		if (!var->cmds[i])
			ft_exit(var, ft_perror("", strerror(errno), "", errno));
		var->cmds[i][0] = ft_cmd_resolve(var, i);
	}
}

int	main(int ac, char **av, char **env)
{
	int		i;
	t_var	var;

	ft_bzero(&var, sizeof(t_var));
	var.hdoc = 1;
	if (ac != 1)
		ft_exit(&var, ft_perror(" syntax: ", \
				"./minishell", "", 1));
	i = 0;
	while (env[i] && ft_strncmp(env[i], "PATH=", 5))
		i++;
	if (!env[i])
		ft_exit(&var, ft_perror("", strerror(errno), "", errno));
	var.paths = ft_split(env[i] + 5, ':');
	if (!var.paths)
		ft_exit(&var, ft_perror("", strerror(errno), "", errno));
//	var.pipes = (int *)ft_calloc((ac - 4 - var.hdoc) * 2, sizeof(int));
//	if (!var.pipes)
//		ft_exit(&var, ft_perror("", strerror(errno), "", errno));
	ft_open_heredoc(&var, "exit", 4);
	ft_start_args(&var, av, ac);
	ft_exit(&var, ft_pipex(&var, var.hdoc, env, 0));
}
