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

int	ms_regular_token_len(char *line, int i)
{
	int		len;
	char	quote;

	len = 0;
	while (!ft_strchr(" |&<>()", line[len]))
	{
		if (line[len] == '\'' || line[len] == '\"')
		{
			quote = line[len++];
			while (line[len] && line[len] != quote)
				len++;
			if (!line[len])
			{
				ms_perror(&quote, ": error quotes must be closed", "", 1);
				free(line - i);
				return (-1);
			}
		}
		len++;
	}
	return (&line[len] - line);
}

int	ms_special_token_len(char *line, int i)
{
	char	token;

	token = line[0];
	if ((token == '&' && line[1] != '&') || \
		token == '\\' || token == ';' || token == '`')
	{
		ms_perror("syntax error near unexpected token `", &token, "'", 1);
		free(line - i);
		return (-1);
	}
	if (token == '|' || token == '&' || token == '<' || token == '>')
	{
		if (line[0] == line[1])
			return (2);
		return (1);
	}
	if (line[0] == '(' || line[0] == ')')
		return (1);
	return (0);
}

int	ms_fill_tokens(char *line, char **tokens)
{
	int	token_len;

	while (*line)
	{
		while (*line == ' ')
			line++;
		if (!*line)
			break ;
		token_len = ms_special_token_len(line, 0);
		if (token_len < 0)
			return (-1);
		else if (token_len > 0)
		{
			*tokens++ = ft_substr(line, 0, token_len);
			line += token_len;
			continue ;
		}
		token_len = ms_regular_token_len(line, 0);
		if (token_len < 0)
			return (-1);
		*tokens++ = ft_substr(line, 0, token_len);
		line += token_len;
	}
	return (0);
}

int	ms_token_counter(t_var *var)
{
	int	i;
	int	token_len;
	int	token_count;

	i = 0;
	token_count = 0;
	while (var->line[i])
	{
		while (var->line[i] == ' ')
			i++;
		if (var->line[i])
			token_count++;
		token_len = ms_special_token_len(&var->line[i], i);
		if (token_len < 0)
			return (-1);
		i += token_len;
		if (token_len > 0)
			continue ;
		token_len = ms_regular_token_len(&var->line[i], i);
		if (token_len < 0)
			return (-1);
		i += token_len;
	}
	return (token_count);
}
