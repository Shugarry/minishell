/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miggarc2 <miggarc2@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 17:10:44 by miggarc2          #+#    #+#             */
/*   Updated: 2025/06/23 07:21:23 by frey-gal         ###   ########.fr       */
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
	char			*line;
	int				*pipes;
	int				hd_int;
	int				fd_in;
	int				fd_out;
	int				pipe_count;
	int				cmd_count;
	int				token_count;
	char			***cmds;
	char			**cmd_splitters;
	char			**tokens;
	char			**env;
	int				env_len;
	char			**paths;
	char			pwd[4096];
	unsigned char	exit_code;
	t_list			*memlist;
}					t_var;

// minishell_exec.c
_Bool	ms_exec_builtins(t_var *var, int i);
void	ft_exec_child(t_var *var, int i, int pipes);
int		ms_pipex(t_var *var);
int		ms_redirect_cmds(t_var *var, int i);

// minishell_init.c
void	ms_open_heredoc(char *limit, size_t limit_len, int *hd_int);
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
_Bool	ms_token_filler(char *line, char **tokens);

// minishell_utils.c
int		ms_perror(char *err1, char *err2, char *err3, int err_no);
void	ms_free_ptrs(t_var *var);
void	ms_clean(char **var_ptr);
void	ms_exit(t_var *var, int exit_code);

// minishell_memory.c
void	*memlist_alloc(t_var *var, size_t size);
void	*memlist_add(t_var *var, void *ptr);
void	memlist_free_all(t_var *var);
void	memlist_free_ptr(t_var *var, void *ptr);

// minishell_builtins.c
void	ms_echo(char **tokens);
void	ms_cd(t_var *var, char **tokens);
void	ms_pwd(t_var *var);
void	ms_export(t_var *var, char **tokens);
void	ms_unset(t_var *var, char **tokens);
void	ms_env(t_var *var);

// minishell_variables.c
void	add_env_var(t_var *var, char *variable);
void	remove_env_var(t_var *var, char *var_name);
void	create_env(t_var *var, char **env);
void	modify_env_var(t_var *var, char *var_name, char *new_content);
char	*get_env_var(t_var *var, char *variable);

// minishell_processing.c
bool	is_escape_char(char c);
int		var_len_diff(t_var *var, char *str);
char	*var_finder(t_var *var, char *str, char *new_token);
int		new_token_size(t_var *var, char *token);
char	*token_builder(t_var *var, char *token);
char	**expand_cmd(t_var *var, char **cmd);
_Bool	ms_cmd_expander(t_var *var);

#endif
