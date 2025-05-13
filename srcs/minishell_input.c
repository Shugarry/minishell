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

static int	ft_word_count(char const *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s && s[i])
	{
		if (s[i] != c)
		{
			count++;
			while (s[i] && s[i] != c)
				i++;
		}
		while (s[i] == c)
			i++;
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

void	ft_start_args(t_var *var, char **av, int ac)
{
	int	i;

	var->cmds = (char ***)ft_calloc(ac + 1, sizeof(char **));
	if (!var->cmds)
		ft_exit(var, ft_perror("", strerror(errno), "", errno));
	i = -1;
	while (++i < ac)
	{
		var->cmds[i] = ft_split(av[i], ' ');	
		if (!var->cmds[i])
			ft_exit(var, ft_perror("", strerror(errno), "", errno));
		var->cmds[i][0] = ft_cmd_resolve(var, i);
	}
	var->cmds[i] = NULL;
}

void	ft_start_mini(t_var *var)
{
	char	*line;
	char	**args;
	int		word_count;

	while (1)
	{
		line = readline("minishell$ ");
		if (!line)
			break ;
		// Pend tokenize



		if (ft_strncmp(line, "exit\0", 5) == 0)
		{
			close(STDIN_FILENO);
			free(line);
			line = readline("exit\n");
			break ;
		}
		else if (*line != '\0')
		{
			add_history(line);
			args = ft_split(line, '|');
			word_count = ft_word_count(line, '|');
			var->pipes = (int *)ft_calloc((word_count - 1) * 2, sizeof(int));
       		if (word_count > 1 && !var->pipes)
				ft_exit(var, ft_perror("", strerror(errno), "", errno));
			ft_start_args(var, args, word_count);
			ft_pipex(var, word_count - 1, var->env, 0);
			if (var->pipes)
				free(var->pipes);
			ft_clean(args);
			if (var->cmds)
			{
				int i = 0;
				while (var->cmds[i])
					ft_clean(var->cmds[i++]);
				free(var->cmds);
			}
		}
		free(line);
	}
}

int	main(int ac, char **av, char **env)
{
	t_var	var;

	ft_bzero(&var, sizeof(t_var));
	if (ac != 1)
		ft_exit(&var, ft_perror(" syntax: ", "./minishell", "", 1));
	var.av = av;
	var.env = env;
	if (!(*var.env))	// Pend use getenv_plus
		*var.env = getcwd(var.pwd, sizeof(var.pwd));
	else
		*var.env = getenv("PATH");
	var.paths = ft_split(*var.env, ':');
	if (!var.paths)
		ft_exit(&var, ft_perror("", strerror(errno), "", errno));
	ft_start_mini(&var);
}
