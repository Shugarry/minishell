/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_builtins_vars.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frey-gal <frey-gal@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 19:33:08 by frey-gal          #+#    #+#             */
/*   Updated: 2025/07/10 19:34:05 by frey-gal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stdio.h>
#include <unistd.h>

static void	export_print(t_var *var)
{
	int		j;
	char	*variable;
	char	*content;

	j = 0;
	while (var->env[j])
	{
		variable = memlist_add(var, ft_strdup(var->env[j]));
		content = ft_strchr(variable, '=');
		if (content)
		{
			content[0] = '\0';
			content++;
			printf("declare -x %s=\"%s\"\n", variable, content);
		}
		else if (!content)
			printf("declare -x %s\n", variable);
		j++;
		memlist_free_ptr(var, variable);
	}
}

static void	export_add(t_var *var, char *token)
{
	char	*variable;
	char	*content;
	int		j;

	j = 0;
	variable = memlist_add(var, ft_strdup(token));
	content = ft_strchr(variable, '=');
	if (content)
		*content++ = '\0';
	while ((variable && variable[j]) || token[0] == '=')
	{
		if (token[0] == '=' || (!ft_isalpha(variable[0]) && variable[0] != '_')
			|| (!ft_isalnum(variable[j]) && variable[j] != '_'))
		{
			var->exit_code = 1;
			ms_perror("minishell: export: `", token,
			 "': not a valid identifier", 1);
			memlist_free_ptr(var, variable);
			return ;
		}
		j++;
	}
	modify_env_var(var, variable, content);
	memlist_free_ptr(var, variable);
}

void	ms_export(t_var *var, char **tokens)
{
	int		i;

	i = 1;
	if (!tokens[i])
		export_print(var);
	while (tokens[i])
	{
		var->exit_code = 0;
		export_add(var, tokens[i]);
		i++;
	}
}

void	ms_unset(t_var *var, char **tokens)
{
	int	i;

	i = 1;
	while (tokens[i])
	{
		remove_env_var(var, tokens[i]);
		i++;
	}
}

void	ms_env(t_var *var, char **tokens)
{
	int	i;

	i = 0;
	if (tokens[1])
	{
		var->exit_code = 127;
		ms_perror("minishell: env: '", tokens[1],
			"': No such file or directory\n", 127);
		return ;
	}
	while (var->env[i] != NULL)
	{
		if (ft_strchr(var->env[i], '='))
			printf("%s\n", var->env[i]);
		i++;
	}
}
