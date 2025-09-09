/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_token_validation.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frey-gal <frey-gal@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 04:12:08 by frey-gal          #+#    #+#             */
/*   Updated: 2025/09/09 05:08:53 by frey-gal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static bool	is_invalid_char(char c)
{
	return (c == '`' || c == ';' || c == '\\' || c == '{' || c == '}'
	|| c == '(' || c == ')' || c == '&' );
}

static bool	is_special_token(char *token)
{
	if (!token || !*token)
		return (false);
	else if (ft_strncmp(token, ">", 2) == 0)
		return (true);
	else if (ft_strncmp(token, "<", 2) == 0)
		return (true);
	else if (ft_strncmp(token, ">>", 3) == 0)
		return (true);
	else if (ft_strncmp(token, "<<", 3) == 0)
		return (true);
	else if (ft_strncmp(token, "|", 2) == 0)
		return (true);
	return (false);
}

static bool	token_error(t_var *var, char *token, int len)
{
	char	tmp[len + 1];
	char	*nl_str;

	nl_str = "newline";
	if (token == NULL)
	{
		ms_perror("syntax error near unexpected token `", nl_str, "'", 1);
		var->exit_code = 2;
		return (false);
	}
	ft_strlcpy(tmp, token, len + 1);
	ms_perror("syntax error near unexpected token `", tmp, "'", 1);
	var->exit_code = 2;
	return (false);
}

static bool	are_chars_valid(t_var *var, char *tok)
{
	int		j;
	bool	in_single_quotes;
	bool	in_double_quotes;
	bool	in_quotes;

	in_single_quotes = false;
	in_double_quotes = false;
	j = 0;
	while (tok[j])
	{
		if (tok[j] == '\'' && !in_double_quotes)
			in_single_quotes = !in_single_quotes;
		else if (tok[j] == '"' && !in_single_quotes)
			in_double_quotes = !in_double_quotes;
		in_quotes = in_single_quotes || in_double_quotes;
		if (is_invalid_char(tok[j]) && in_quotes == false)
			return (token_error(var, tok + j, 1));
		j++;
	}
	return (true);
}

bool	valid_tokens(t_var *var, char **toks)
{
	int		i;

	i = 0;
	while (toks[i])
	{
		if (are_chars_valid(var, toks[i]) == false)
			return (false);
		if (is_special_token(toks[i]) && ft_strncmp(toks[i], "|", 2) != 0)
		{
			if (toks[i + 1] == NULL || is_special_token(toks[i + 1]))
				return (token_error(var, toks[i + 1], ft_strlen(toks[i + 1])));
		}	
		else if (ft_strncmp(toks[i], "|", 2) == 0)
		{
			if (i == 0 || toks[i + 1] == NULL ||
				ft_strncmp(toks[i + 1], "|", 2) == 0)
				return (token_error(var, toks[i], ft_strlen(toks[i])));
		}	
		i++;
	}
	return (true);
}
