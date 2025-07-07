/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_processing.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frey-gal <frey-gal@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 01:06:17 by frey-gal          #+#    #+#             */
/*   Updated: 2025/06/26 03:32:05 by frey-gal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	var_len_diff(t_var *var, char *str)
{
	int		i;
	int		len_name;
	int		len_content;
	char	*var_name;
	char	*content;
	
	i = 1;
	var_name = ft_strdup(str + 1);
	if (!var_name)
		ms_exit(var, ms_perror("", "malloc fail()", "", errno));
	while (ft_isalpha(var_name[1])
			&& (ft_isalnum(var_name[i]) || var_name[i] == '_'))
		i++;
	var_name[i] = '\0';
	content = get_env_var(var, var_name);
	if (!content)
		len_content = 0;
	else
		len_content = ft_strlen(content);
	len_name = ft_strlen(var_name);
	free(var_name);
	return (len_content - len_name - 1);
}

char	*var_finder(t_var *var, char *str, char *new_token)
{
	int		i;
	char	*var_name;
	char	*content;
	
	i = 1;
	var_name = ft_strdup(str + 1);
	if (!var_name)
	{
		free(new_token);
		ms_exit(var, ms_perror("", "malloc fail()", "", errno));
	}
	while (ft_isalnum(var_name[i]) || var_name[i] == '_')
		i++;
	var_name[i] = '\0';
	content = get_env_var(var, var_name);
	free(var_name);
	if (!content)
		return ("");
	return (content);
}

int	new_token_size(t_var *var, char *token)
{
	int		len;
	int		i;
	bool	in_single;
	bool	in_double;

	len = ft_strlen(token);
	i = 0;
	in_single = false;
	in_double = false;
	while (token[i])
	{
		if (token[i] == '$' && !in_single && (ft_isalpha(token[i + 1])
				|| token[i + 1] == '_'))
		{
			len += var_len_diff(var, token + i);
			i++;
			while (ft_isalnum(token[i]) || token[i] == '_')
				i++;
			continue ;
		}
		if (token[i] == '"' && !in_single)
		{
			in_double = !in_double;
			len--;
		}
		else if (token[i] == '\'' && !in_double)
		{
			in_single = !in_single;
			len--;
		}
		i++;
	}
	return (len);
}

char	*token_builder(t_var *var, char *token)
{
	char	*new_token;
	char	*tmp;
	int		len;
	int		i;
	int		j;
	bool	in_single;
	bool	in_double;

	len = new_token_size(var, token);
	if (!len)
		return (ft_strdup(""));
	new_token = (char *)malloc(sizeof(char) * (len + 1));
	if (!new_token)
		return (NULL);
	i = 0;
	j = 0;
	in_single = false;
	in_double = false;
	while (token[j])
	{
		if (token[j] == '$' && !in_single && (ft_isalpha(token[j + 1])
				|| token[j + 1] == '_'))
		{
			tmp = var_finder(var, token + j, new_token);
			i += ft_strlcpy(new_token + i, tmp, ft_strlen(tmp) + 1);
			j++;
			while (ft_isalnum(token[j]) || token[j] == '_')
				j++;
		}
		else if (token[j] == '"' && !in_single)
		{
			in_double = !in_double;
			j++;
		}
		else if (token[j] == '\'' && !in_double)
		{
			in_single = !in_single;
			j++;
		}
		else
		{
			new_token[i] = token[j];
			i++;
			j++;
		}
	}
	new_token[i] = '\0';
	return (new_token);
}

char	**expand_cmd(t_var *var, char **cmd)
{
	int		i;
	char	*tmp;

	i = 0;
	while (cmd[i])
	{
		tmp = cmd[i];
		cmd[i] = token_builder(var, cmd[i]);
		if (!cmd[i])
		{
			ms_clean(cmd);
			ms_exit(var, ms_perror("", "malloc() fail", "", errno));
		}
		free(tmp);
		i++;
	}
	return (cmd);
}

_Bool	ms_cmd_expander(t_var *var)
{
	int		i;

	i = 0;
	while (var->cmds[i])
	{
		var->cmds[i] = expand_cmd(var, var->cmds[i]);
		i++;
	}
	return (false);
}
