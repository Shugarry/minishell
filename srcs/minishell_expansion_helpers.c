/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_expansion_helpers.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frey-gal <frey-gal@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 21:16:44 by frey-gal          #+#    #+#             */
/*   Updated: 2025/07/10 21:19:07 by frey-gal         ###   ########.fr       */
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
	if (ft_strncmp("$?", str, 2) == 0)
		return (2 - ft_strlen(get_env_var(var, "?")) - 1);
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
	if (ft_strncmp("$?", str, 2) == 0)
		return (get_env_var(var, "?"));
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
