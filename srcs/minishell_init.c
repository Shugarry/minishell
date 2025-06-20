/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_init.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miggarc2 <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 19:02:08 by miggarc2          #+#    #+#             */
/*   Updated: 2025/06/06 03:52:58 by frey-gal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ms_cmd_resolve(t_var *var, int i)
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
	{
		free(var->cmds[i][0]);
		var->cmds[i][0] = cmd;
	}
}

_Bool	ms_cmd_filler(t_var *var)
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
			!ft_strchr("|&()", *var->tokens[i + args]))
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

char	**dup_str_arr(t_var *var)
{
	char	**new_arr;
	int	i;

	i = 0;
	while (var->cmds[i])
		i++;
	new_arr = memlist_alloc(&var->memlist, i * (sizeof(char *) + 1));
	if (!new_arr)
		ms_exit(var, ms_perror("", strerror(errno), "", errno));
	i = 0;
	while (var->cmds[i])
	{
		new_arr[i] = memlist_add(&var->memlist, ft_strdup(var->cmds[i]));
		i++;
	}
	return (new_arr);
}

char	**clean_cmd(char	**arr)
{

}

_Bool	ms_cmd_cleaner(t_var *var)
{
	int		i;
	char	***tmp;

	tmp = var->cmds;
	while(var->cmds[i])
	{
		var->cmds[i] = clean_cmd(var->cmds[i]);
		ms_clean(var->cmds[i]);
	}
	return false;
}

_Bool	ms_start_args(t_var *var)
{
	int		i;

	var->tokens = (char **)ft_calloc(var->token_count + 1, sizeof(char *));
	var->cmds = (char ***)ft_calloc(var->cmd_count + 1, sizeof(char **));
	var->cmd_splitters = (char **)ft_calloc(var->cmd_count, sizeof(char *));
	var->pipes = (int *)ft_calloc((var->pipe_count) * 2, sizeof(int));
	if (!var->tokens || !var->cmds || !var->cmd_splitters || \
		(var->pipe_count && !var->pipes))
		return (ms_perror("", strerror(errno), "", errno));
	if (ms_token_filler(var->line, var->tokens) || ms_cmd_filler(var) ||
		ms_cmd_cleaner(var))
		return (1);
	i = -1;
	while (var->cmds[++i])
		ms_cmd_resolve(var, i);
	return (0);
}

int	main(int ac, char **av, char **env)
{
	t_var	var;

	ft_bzero(&var, sizeof(t_var));
	if (ac != 1 || av[1])
		ms_exit(&var, ms_perror("", "arguments are not supported yet", "", 1));
	if (!env || !*env)
		ms_exit(&var, ms_perror("", "env not found", "", 1));
	var.tokens = NULL;
	var.env = env;
	var.paths = ft_split(getenv("PATH"), ':');
	create_var_list(&var, env);
	if (!var.paths)
		ms_exit(&var, ms_perror("", strerror(errno), "", errno));
	while (1)
	{
		signal(SIGINT, ms_signal_handle);
		signal(SIGQUIT, SIG_IGN);
		var.line = readline(GREEN "minishell$ " RESET);
		if (!var.line)
			ms_exit(&var, 0);
		var.cmd_count = 1;
		if (*var.line)
			add_history(var.line);
		if (!ms_token_counter(var.line, &var) && !ms_start_args(&var))
			ms_pipex(&var);
		ms_free_ptrs(&var);
	}
}
