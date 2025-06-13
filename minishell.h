/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miggarc2 <miggarc2@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 17:10:44 by miggarc2          #+#    #+#             */
/*   Updated: 2025/05/07 21:16:01 by miggarc2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <stdbool.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <sys/wait.h>
# include <string.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>

# define GREEN "\033[0;32m"
# define RESET "\033[0m"

extern volatile sig_atomic_t	g_signal_code;

typedef struct s_var
{
	_Bool	hdoc;
	char	*line;
	int		*pipes;
	int		fd_in;
	int		fd_out;
	int		pipe_count;
	int		cmd_count;
	int		token_count;
	char	***cmds;
	char	**cmd_splitters;
	char	**tokens;
	char	**env;
	char	**paths;
	char	pwd[4096];
	int		exit_code;
}			t_var;

// minishell_exec.c
void	ft_exec_child(t_var *var, int i, int end);
_Bool	ms_exec_builtins(t_var *var, int i);
int		ms_pipex(t_var *var, int end);

// minishell_init.c
void	ms_cmd_resolve(t_var *var, int i);
_Bool	ms_cmd_filler(t_var *var);
_Bool	ms_start_args(t_var *va);
int		main(int ac, char **av, char **env);

// minishell_signals.c
void	ms_signal_handle(int sig);
void	ms_signal_handle_child(int sig);

// minishell_tokens.c
int		ms_regular_token_check(char *line);
int		ms_special_token_check(char *line, t_var *var);
_Bool	ms_token_counter(char *line, t_var *var);
_Bool		ms_token_filler(char *line, char **tokens);

// minishell_utils.c
int		ms_perror(char *err1, char *err2, char *err3, int err_no);
void	ms_free_ptrs(t_var *var);
void	ms_clean(char **var_ptr);
void	ms_exit(t_var *var, int exit_code);

#endif
