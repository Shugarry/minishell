/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_heredoc_helpers.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frey-gal <frey-gal@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 20:09:40 by frey-gal          #+#    #+#             */
/*   Updated: 2025/09/03 20:38:07 by frey-gal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	new_hd_line_len(t_var *var, char *line, int len)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '$' && (ft_isalpha(line[i + 1])
				|| line[i + 1] == '_' || line[i + 1] == '?'))
		{
			len += var_len_diff(var, line + i);
			i++;
			if (line[i] == '?')
				i++;
			else
				while (ft_isalnum(line[i]) || line[i] == '_')
					i++;
		}
		else
			i++;
	}
	return (len);
}

static bool	bnl_if_helper(char *line, int i)
{
	return (line[i] == '$' && (ft_isalpha(line[i + 1])
			|| line[i + 1] == '_' || line[i + 1] == '?'));
}

static char	*build_new_line(t_var *var, char *line, int new_len)
{
	int		i;
	int		j;
	char	*tmp;
	char	*new_line;

	i = 0;
	j = 0;
	new_line = (char *)memlist_alloc(var, sizeof(char) * (new_len + 1));
	while (line[i])
	{
		if (bnl_if_helper(line, i))
		{
			tmp = var_finder(var, line + i, NULL);
			j += ft_strlcpy(new_line + j, tmp, ft_strlen(tmp) + 1);
			if (line[++i] == '?')
				i++;
			else
				while (ft_isalnum(line[i]) || line[i] == '_')
					i++;
		}
		else
			new_line[j++] = line[i++];
	}
	new_line[j] = '\0';
	return (new_line);
}

char	*hd_var_expansion(t_var *var, char *line)
{
	int		len;
	int		new_len;
	char	*new_line;

	len = ft_strlen(line);
	new_len = new_hd_line_len(var, line, len);
	new_line = build_new_line(var, line, new_len);
	return (new_line);
}
