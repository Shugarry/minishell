/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_helpers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frey-gal <frey-gal@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 21:08:00 by frey-gal          #+#    #+#             */
/*   Updated: 2025/09/12 21:09:18 by frey-gal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	check_hd_expansion(t_var *var)
{
	int	i;

	i = ft_strlen(var->line);
	while (i >= 0)
	{
		if (i > 0 && var->line[i] == '<' && var->line[i - 1] == '<')
		{
			while (var->line[i])
			{
				if (var->line[i] == '\'')
					return (false);
				i++;
			}
			break ;
		}
		i--;
	}
	return (true);
}

static void	child_hd_helper(char *line, int here_fd, int l_no, char *limit)
{
	if (line)
		free(line);
	close(here_fd);
	if (line == NULL)
		printf("warn: here-doc at line %d limited by `%s'\n", l_no, limit);
	exit(0);
}

void	ms_child_hd(t_var *var, char *limit, size_t limit_len, int here_fd)
{
	char	*line;
	char	*tmp;
	int		l_no;

	l_no = 0;
	while (++l_no)
	{
		line = readline("> ");
		if (line && ft_strncmp(line, limit, limit_len))
		{
			if (check_hd_expansion(var) == true)
				tmp = hd_var_expansion(var, line);
			else
				tmp = memlist_add(var, ft_strdup(line));
			ft_putendl_fd(tmp, here_fd);
			memlist_free_ptr(var, tmp);
		}
		else
			break ;
		free(line);
	}
	child_hd_helper(line, here_fd, l_no, limit);
}

static void	skip_token(char *line, int *i)
{
	char	quote;

	if (line[*i] == '"' || line[*i] == '\'')
	{
		quote = line[(*i)++];
		while (line[*i] && line[*i] != quote)
			(*i)++;
		if (line[*i])
			(*i)++;
	}
	else
	{
		while (line[*i] && !ft_strchr(" |<>\"'", line[*i]))
			(*i)++;
	}
}

bool	was_token_quoted(t_var *var, int cmd_idx, int token_idx)
{
	char	*line;
	int		i;
	int		current_cmd;
	int		current_token;

	line = var->line;
	i = 0;
	current_cmd = 0;
	current_token = 0;
	while (current_cmd < cmd_idx && line[i])
		if (line[i++] == '|')
			current_cmd++;
	while (line[i] && line[i] != '|')
	{
		while (line[i] == ' ')
			i++;
		if (!line[i] || line[i] == '|')
			break ;
		if (current_token == token_idx)
			return (line[i] == '"' || line[i] == '\'');
		skip_token(line, &i);
		current_token++;
	}
	return (false);
}
