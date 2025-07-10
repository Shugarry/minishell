/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_expansion.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frey-gal <frey-gal@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 01:06:17 by frey-gal          #+#    #+#             */
/*   Updated: 2025/07/10 21:18:06 by frey-gal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	token_size_logic(t_var *var, char *token, int *len, t_builder *b)
{
	if (token[b->i] == '$' && !b->in_single && (ft_isalpha(token[b->i + 1])
			|| token[b->i + 1] == '_'))
	{
		len += var_len_diff(var, token + b->i);
		b->i++;
		while (ft_isalnum(token[b->i]) || token[b->i] == '_')
			b->i++;
		return ;
	}
	if (token[b->i] == '"' && !b->in_single)
	{
		b->in_double = !b->in_double;
		len--;
	}
	else if (token[b->i] == '\'' && !b->in_double)
	{
		b->in_single = !b->in_single;
		len--;
	}
	b->i++;
}

int	new_token_size(t_var *var, char *token)
{
	int			len;
	t_builder	b;

	len = ft_strlen(token);
	ft_bzero(&b, sizeof(t_builder));
	while (token[b.i])
		token_size_logic(var, token, &len, &b);
	return (len);
}

static void	token_builder_logic(t_builder *b, char *token, t_var *var)
{
	char	*tmp;

	if (token[b->j] == '$' && !b->in_single && (ft_isalpha(token[b->j + 1])
			|| token[b->j + 1] == '_'))
	{
		tmp = var_finder(var, token + b->j, b->new_token);
		b->i += ft_strlcpy(b->new_token + b->i, tmp, ft_strlen(tmp) + 1);
		b->j++;
		while (ft_isalnum(token[b->j]) || token[b->j] == '_')
			b->j++;
	}
	else if (token[b->j] == '"' && !b->in_single)
	{
		b->in_double = !b->in_double;
		b->j++;
	}
	else if (token[b->j] == '\'' && !b->in_double)
	{
		b->in_single = !b->in_single;
		b->j++;
	}
	else
		b->new_token[b->i++] = token[b->j++];
}

char	*token_builder(t_var *var, char *token)
{
	t_builder	b;
	int			len;

	len = new_token_size(var, token);
	if (!len)
		return (ft_strdup(""));
	ft_bzero(&b, sizeof(t_builder));
	b.new_token = (char *)malloc(sizeof(char) * (len + 1));
	if (!b.new_token)
		return (NULL);
	while (token[b.j])
		token_builder_logic(&b, token, var);
	b.new_token[b.i] = '\0';
	return (b.new_token);
}

bool	expand_cmd(t_var *var)
{
	int		i;
	int		j;
	char	*tmp;

	i = -1;
	while (var->cmds[++i])
	{
		j = -1;
		while (var->cmds[i][++j])
		{
			tmp = var->cmds[i][j];
			var->cmds[i][j] = token_builder(var, var->cmds[i][j]);
			free(tmp);
			if (!var->cmds[i][j])
				ms_exit(var, ms_perror("", "malloc() fail", "", errno));
		}
	}
	return (0);
}
