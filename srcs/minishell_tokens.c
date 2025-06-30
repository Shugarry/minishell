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

#include "../minishell.h"

int	ms_regular_token_check(char *line)
{
	int		len;
	char	quote;

	len = 0;
	while (!ft_strchr(" |<>", line[len]))
	{
		if (line[len] == '\'' || line[len] == '\"')
		{
			quote = line[len++];
			while (line[len] && line[len] != quote)
				len++;
			if (!line[len])
			{
				ms_perror(&quote, ": error quotes must be closed", "", 1);
				return (-1);
			}
		}
		len++;
	}
	return (&line[len] - line);
}

int	ms_special_token_check(char *line, t_var *var)
{
	char	token[2];

	token[0] = line[0];
	token[1] = '\0';
	if (*token == '\\' || *token == ';' || *token == '`')
	{
		ms_perror("syntax error near unexpected token `", token, "'", 1);
		return (-1);
	}
	if (*token == '|' || *token == '<' || *token == '>')
	{
		if (var && *token == '|')
		{
			var->cmd_count++;
			var->pipe_count++;
		}
		if (line[0] == line[1] && (*token == '<' || *token == '>'))
			return (2);
		return (1);
	}
	return (0);
}

_Bool	ms_token_counter(char *line, t_var *var)
{
	int	i;
	int	token_len;

	i = 0;
	var->token_count = 0;
	if (var->pipe_count)
		var->pipe_count = 0;
	while (line[i])
	{
		while (line[i] == ' ')
			i++;
		if (line[i])
			var->token_count++;
		token_len = ms_special_token_check(&line[i], var);
		if (token_len < 0)
			return (1);
		i += token_len;
		if (token_len > 0)
			continue ;
		token_len = ms_regular_token_check(&line[i]);
		if (token_len < 0)
			return (1);
		i += token_len;
	}
	return (0);
}

_Bool	ms_token_filler(char *line, char **tokens)
{
	int	token_len;

	while (*line)
	{
		while (*line == ' ')
			line++;
		if (!*line)
			break ;
		token_len = ms_special_token_check(line, NULL);
		if (token_len < 0)
			return (1);
		else if (token_len > 0)
		{
			*tokens++ = ft_substr(line, 0, token_len);
			line += token_len;
			continue ;
		}
		token_len = ms_regular_token_check(line);
		if (token_len < 0)
			return (1);
		*tokens++ = ft_substr(line, 0, token_len);
		line += token_len;
	}
	return (0);
}
