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

volatile sig_atomic_t	g_signal_code = 0; // NOTE:: GLOBALES SOLO STATIC O CONST Y EN EL HEADER (MIRAR NORMA)
//NORM: Declaration and an initialisation cannot be on the same line, except for global
 //variables (when allowed), static variables, and constants. (it's enumerating different kinds of variables)
 //Also in C the global variables can be declared as extern in the .h, but defined (valor assign)
 //in the .c files, otherwise it wil generate conflicts.

void	ms_signal_handle(int sig)
{
	if (sig == SIGINT)
	{
		ft_putendl_fd("", STDOUT_FILENO);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_signal_code = 130;
	}
}

void	ms_signal_handle_hd(int sig)
{
	if (sig == SIGINT)
	{
		g_signal_code = 130;
		write(STDIN_FILENO, "\n", 1);
	}
}

void	ms_signal_handle_child(int sig)
{
	if (sig == SIGINT)
	{
		ft_putendl_fd("", STDOUT_FILENO);
		rl_on_new_line();
		g_signal_code = 130;
	}
	else if (sig == SIGQUIT)
	{
		ft_putendl_fd("Quit (core dumped)", STDOUT_FILENO);
		g_signal_code = 131;
	}
}

void	catch_and_get_signal(t_var *var)
{
	if (g_signal_code)
	{
		var->exit_code = g_signal_code;
		g_signal_code = 0;
	}
}
