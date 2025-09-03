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
	return (len);
}

static void	build_new_line(t_var *var, char *line, int len)
{
	int		i;
	int		j;
	char	*new_line;

	i = 0;
	j = 0;
	while ()
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
	}
}

char	*hd_var_expansion(t_var *var, char *line)
{
	int		i;
	int		len;
	int		new_len;
	char	*new_line;

	i = 0;
	len = ft_strlen(line);
	new_len = new_hd_line_len(var, line, len);
}
