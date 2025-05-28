/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_input.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miggarc2 <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 19:02:08 by miggarc2          #+#    #+#             */
/*   Updated: 2025/05/08 20:29:16 by miggarc2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_pipe_count(char const *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s && s[i])
	{
		if (s[i] != c)
			while (s[i] && s[i] != c)
				i++;
		else
		{
			count++;
			i++;
		}
	}
	return (count);
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

_Bool	ms_start_args(t_var *var, int cmd_count)
{
	int		i;

	var->cmds = (char ***)ft_calloc(cmd_count + 1, sizeof(char **));
	if (!var->cmds)
		ft_exit(var, ft_perror("", strerror(errno), "", errno));
	var->cmds[cmd_count] = NULL;
	var->args = ft_split(var->line, '|');
	if (!var->args)
		ft_exit(var, ft_perror("", strerror(errno), "", errno));
	i = -1;
	while (++i < cmd_count)
	{
		var->cmds[i] = ft_split(var->args[i], ' ');
		if (!var->cmds[i])
			ft_exit(var, ft_perror("", strerror(errno), "", errno));
		else if (!var->cmds[i][0])
		{
			ft_perror("", "syntax error near unexpected token `|'", "", errno);
			ft_clean(var->args);
			i = 0;
			while (var->cmds[i])
				ft_clean(var->cmds[i++]);
			free(var->cmds);
			var->cmds = NULL;
			return (1);
		}
		var->cmds[i][0] = ft_cmd_resolve(var, i);
	}
	ft_clean(var->args);
	return (0);
}

_Bool	ms_tokenize(t_var *var)
{
	int		token_count;
	int		i;

	i = 0;
	token_count = 0;
	while (var->line[i])
	{
		while (var->line[i] == ' ')
			i++;
		if (var->line[i] == '&' && var->line[i + 1] != '&')
		{
			ft_perror("", "syntax error near unexpected token `&'", "", 1);
			free(var->line);
			return (1);
		}
		if (var->line[i])
			token_count++;
		if (var->line[i] && ft_strchr("|&<>()", var->line[i]))
		{
			if ((var->line[i] == '|' && var->line[i + 1] == '|') || \
				(var->line[i] == '&' && var->line[i + 1] == '&') || \
				(var->line[i] == '<' && var->line[i + 1] == '<') || \
				(var->line[i] == '>' && var->line[i + 1] == '>'))
				i++;
			i++;
			continue ;
		}
		while (!ft_strchr(" |&<>()", var->line[i]))
		{
			i++;
			if (var->line[i - 1] == '\'' || var->line[i - 1] == '\"')
			{
				if (var->line[i - 1] == '\'' && ft_strchr(&var->line[i], '\''))
					i += ft_strchr(&var->line[i], '\'') - &var->line[i];
				else if (var->line[i - 1] == '\"' && \
					ft_strchr(&var->line[i], '\"'))
					i += ft_strchr(&var->line[i], '\"') - &var->line[i];
				else
				{
					ft_perror("", "syntax error quotes must be closed", "", 1);
					free(var->line);
					return (1);
				}
				i++;
			}
		}
	}
	printf("token_count: %d\n", token_count);
	return (0);
}

void	ms_start_mini(t_var *var)
{
	int	pipe_count;
	int	i;

	while (1)
	{
		signal(SIGINT, ms_signal_handle);
		signal(SIGQUIT, SIG_IGN);
		var->line = readline(GREEN "minishell$ " RESET);
		if (!var->line)
			ft_exit(var, 0);
		if (*var->line != '\0')
		{
			add_history(var->line);
			if (ms_tokenize(var))
				continue ;
			pipe_count = ms_pipe_count(var->line, '|');
			var->pipes = (int *)ft_calloc((pipe_count) * 2, sizeof(int));
			if (pipe_count && !var->pipes)
				ft_exit(var, ft_perror("", strerror(errno), "", errno));
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
					ft_clean(var->cmds[i++]);
				free(var->cmds);
				var->cmds = NULL;
			}
		}
		free(var->line);
	}
}
