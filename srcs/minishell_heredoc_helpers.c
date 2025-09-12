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

static char	*build_new_line(t_var *var, char *line, int new_len)
{
	int		i;
	int		j;
	char	*new_line;

	i = 0;
	j = 0;
	new_line = (char *)memlist_alloc(var, sizeof(char) * (new_len + 1));
	while (line[i])
	{
		if (line[i] == '$' && (ft_isalpha(line[i + 1]) \
			|| line[i + 1] == '_' || line[i + 1] == '?'))
		{
			j += ft_strlcpy(new_line + j, var_finder(var, line + i, NULL), \
			ft_strlen(var_finder(var, line + i, NULL)) + 1);
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
			tmp = hd_var_expansion(var, line);
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

bool	ms_open_heredoc(t_var *var, char *limit, size_t limit_len, int *hd_int)
{
	int		here_fd;
	char	*hd_no;
	char	*hd_name;
	pid_t	child;
	int		status;

	hd_no = ft_itoa((*hd_int)++);
	hd_name = ft_strjoin(".here_doc_", hd_no);
	if (!hd_no || !hd_name)
		ms_perror("", strerror(errno), "\n", errno);
	free(hd_no);
	here_fd = open(hd_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	free(hd_name);
	if (here_fd < 0)
		ms_perror("", strerror(errno), "\n", errno);
	signal(SIGINT, ms_signal_handle_hd);
	child = fork();
	if (child == 0)
		ms_child_hd(var, limit, limit_len, here_fd);
	signal(SIGINT, ms_signal_handle);
	if ((child < 0 && ms_perror("", strerror(errno), "", errno)) || \
		(waitpid(child, &status, 0) == child && WIFEXITED(status) \
		&& WEXITSTATUS(status) == 130))
		return (1);
	return (0);
}
