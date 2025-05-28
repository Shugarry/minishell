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

int	main(int ac, char **av, char **env)
{
	t_var	var;

	(void)av;
	ft_bzero(&var, sizeof(t_var));
	if (ac != 1)
		ft_exit(&var, ft_perror("", "usage: ./minishell", "", 1));
	if (!env || !*env)
		ft_exit(&var, ft_perror("", "env not found", "", 1));
	var.env = env;
	var.paths = ft_split(getenv("PATH"), ':');
	if (!var.paths)
		ft_exit(&var, ft_perror("", strerror(errno), "", errno));
	ms_start_mini(&var);
}
