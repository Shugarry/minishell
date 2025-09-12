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
	while(i >= 0)
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
	if (line)
		free (line);
	close(here_fd);
	if (line == NULL)
		printf("warn: here-doc at line %d limited by `%s'\n", l_no, limit);
	exit(0);
}
