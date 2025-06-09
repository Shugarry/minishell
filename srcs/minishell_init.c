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

_Bool	ms_start_args(t_var *var, int cmd_count)
{
	int		i;

	var->cmds = (char ***)ft_calloc(cmd_count + 1, sizeof(char **));
	if (!var->cmds)
		ms_exit(var, ms_perror("", strerror(errno), "", errno));
	var->cmds[cmd_count] = NULL;
	var->args = ft_split(var->line, '|');
	if (!var->args)
		ms_exit(var, ms_perror("", strerror(errno), "", errno));
	i = -1;
	while (++i < cmd_count)
	{
		var->cmds[i] = ft_split(var->args[i], ' ');
		if (!var->cmds[i])
			ms_exit(var, ms_perror("", strerror(errno), "", errno));
		else if (!var->cmds[i][0])
		{
			ms_perror("syntax error near unexpected token `", \
				var->cmds[i][0], "'", errno);
			ms_clean(var->args);
			i = 0;
			while (var->cmds[i])
				ms_clean(var->cmds[i++]);
			free(var->cmds);
			var->cmds = NULL;
			return (1);
		}
		var->cmds[i][0] = ft_cmd_resolve(var, i);
	}
	ms_clean(var->args);
	return (0);
}

void	ms_start_mini(t_var *var)
{
	int	i;
	int	token_count;
	int	pipe_count;

	while (1)
	{
		signal(SIGINT, ms_signal_handle);
		signal(SIGQUIT, SIG_IGN);
		var->line = readline(GREEN "minishell$ " RESET);
		if (!var->line)
			ms_exit(var, 0);
		if (*var->line != '\0')
		{
			token_count = ms_token_counter(var);
			if (token_count)
				add_history(var->line);
			if (token_count <= 0)
				continue ;
			if (var->tokens)
				ms_clean(var->tokens);
			var->tokens = (char **)ft_calloc(token_count + 1, sizeof(char *));
			if (!var->tokens)
				ms_exit(var, ms_perror("", strerror(errno), "", errno));
			ms_fill_tokens(var->line, var->tokens);
			i = 0;
			pipe_count = 0;
			while (var->tokens[i])
				if (ft_strncmp(var->tokens[i++], "|", 2) == 0)
					pipe_count++;
			var->pipes = (int *)ft_calloc((pipe_count) * 2, sizeof(int));
			if (pipe_count && !var->pipes)
				ms_exit(var, ms_perror("", strerror(errno), "", errno));
			if (ms_start_args(var, pipe_count + 1))
				continue ;
			ms_pipex(var, pipe_count);
			if (var->pipes)
				free(var->pipes);
			var->pipes = NULL;
			if (var->cmds)
			{
				i = 0;
				while (var->cmds[i])
					ms_clean(var->cmds[i++]);
				free(var->cmds);
				var->cmds = NULL;
			}
		}
		free(var->line);
	}
}

int	main(int ac, char **av, char **env)
{
	t_var	var;

	(void)av;
	ft_bzero(&var, sizeof(t_var));
	if (ac != 1)
		ms_exit(&var, ms_perror("", "usage: ./minishell", "", 1));
	if (!env || !*env)
		ms_exit(&var, ms_perror("", "env not found", "", 1));
	var.tokens = NULL;
	var.env = env;
	var.paths = ft_split(getenv("PATH"), ':');
	create_var_list(&var, env);
	if (!var.paths)
		ms_exit(&var, ms_perror("", strerror(errno), "", errno));
	ms_start_mini(&var);
}
