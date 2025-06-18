/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miggarc2 <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 19:02:08 by miggarc2          #+#    #+#             */
/*   Updated: 2025/05/07 22:34:38 by miggarc2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

volatile sig_atomic_t	g_signal_code = 0;

void	ms_signal_handle(int sig)
{
	if (sig == SIGINT)
	{
		ft_putendl_fd("", STDOUT_FILENO);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	g_signal_code = 130;
}

void	ms_signal_handle_child(int sig)
{
	if (sig == SIGINT)
	{
		ft_putendl_fd("", STDOUT_FILENO);
		g_signal_code = 130;
	}
	else if (sig == SIGQUIT)
	{
		ft_putendl_fd("Quit (core dumped)", STDOUT_FILENO);
		g_signal_code = 131;
	}
}
