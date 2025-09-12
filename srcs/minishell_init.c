/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_init.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miggarc2 <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 19:02:08 by miggarc2          #+#    #+#             */
/*   Updated: 2025/06/23 07:21:23 by frey-gal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ms_cmd_build(t_var *var, int i)
{
	char	*tmp;
	char	*cmd;
	int		j;

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
	{
		free(var->cmds[i][0]);
		return (cmd);
	}
	return (var->cmds[i][0]);
}

bool	ms_cmd_resolve(t_var *var, int i)
{
	int		j;

	j = 0;
	while (var->cmds[i][j])
		if (!ft_strncmp(var->cmds[i][j++], "<<", 3) &&
			ms_open_heredoc(var, var->cmds[i][j],
				ft_strlen(var->cmds[i][j]), &var->hd_int))
			return (1);
	var->hd_int = 0;
	if (var->paths)
		ms_clean(var->paths);
	var->paths = ft_split(get_env_var(var, "PATH"), ':');
	if (!var->paths && get_env_var(var, "PATH"))
		ms_exit(var, ms_perror("", "malloc fail()", "", errno));
	var->cmds[i][0] = ms_cmd_build(var, i);
	return (0);
}

bool	ms_cmd_filler(t_var *var)
{
	int	i;
	int	args;
	int	tmp;

	i = -1;
	var->cmd_count = 0;
	while (var->tokens[++i])
	{
		args = 0;
		while (var->tokens[i + args] && \
			!ft_strchr("|", *var->tokens[i + args]))
			args++;
		var->cmds[var->cmd_count] = \
			(char **)ft_calloc(args + 1, sizeof(char *));
		if (!var->cmds[var->cmd_count])
			return (ms_perror("", strerror(errno), "", errno));
		tmp = 0;
		while (tmp < args)
			var->cmds[var->cmd_count][tmp++] = var->tokens[i++];
		var->cmd_count++;
		if (!var->tokens[i])
			break ;
		var->cmd_splitters[var->cmd_count - 1] = var->tokens[i];
	}
	return (0);
}

bool	ms_start_args(t_var *var)
{
	int	i;

	var->tokens = (char **)ft_calloc(var->token_count + 1, sizeof(char *));
	var->cmds = (char ***)ft_calloc(var->cmd_count + 1, sizeof(char **));
	var->cmd_splitters = (char **)ft_calloc(var->cmd_count, sizeof(char *));
	var->pipes = (int *)ft_calloc((var->pipe_count) * 2, sizeof(int));
	if (!var->tokens || !var->cmds || !var->cmd_splitters || \
		(var->pipe_count && !var->pipes))
		return (ms_perror("", strerror(errno), "", errno));
	if (ms_token_filler(var->line, var->tokens) || ms_cmd_filler(var) || \
		valid_tokens(var, var->tokens) == false || expand_cmd(var))
		return (1);
	i = -1;
	while (var->cmds[++i])
		if (ms_cmd_resolve(var, i))
			return (1);
	return (0);
}

int	main(int ac, char **av, char **env)
{
	t_var	var;

	ft_bzero(&var, sizeof(t_var));
	if (ac != 1 || av[1])
		ms_exit(&var, ms_perror("", "arguments are not supported yet", "", 1));
	create_env(&var, env);
	var.pwd = getcwd_plus(&var);
	while (1)
	{
		signal(SIGINT, ms_signal_handle);
		signal(SIGQUIT, SIG_IGN);
		var.line = readline(GREEN "minishell$ " RESET);
		catch_and_get_signal(&var);
		if (!var.line)
			ms_exit(&var, var.exit_code);
		var.cmd_count = 1;
		if (*var.line)
			add_history(var.line);
		if (!ms_token_counter(var.line, &var) && !ms_start_args(&var))
			ms_pipex(&var);
		ms_free_ptrs(&var);
		var.hd_int = 0;
	}
}
