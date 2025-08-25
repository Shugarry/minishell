/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miggarc2 <miggarc2@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 17:10:44 by miggarc2          #+#    #+#             */
/*   Updated: 2025/07/10 21:30:26 by frey-gal         ###   ########.fr       */
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

typedef struct s_builder
{
	char	*new_token;
	int		i;
	int		j;
	bool	in_single;
	bool	in_double;
}	t_builder;

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
	char			*str_error;
	char			**paths;
	char			*pwd;
	unsigned char	exit_code;
	t_list			*memlist;
}					t_var;

// minishell_exec.c
bool	ms_exec_builtins(t_var *var, int i, bool child);
void	ft_exec_child(t_var *var, int i, int pipes);
int		ms_pipex(t_var *var);
char	**ms_cmd_trim(char **cmd, int pos);
int		ms_open_fds(t_var *var, int i);

// minishell_init.c
void	ms_open_heredoc(char *limit, size_t limit_len, int *hd_int);
void	ms_cmd_resolve(t_var *var, int i);
bool	ms_cmd_filler(t_var *var);
bool	ms_start_args(t_var *va);
int		main(int ac, char **av, char **env);

// minishell_signals.c
void	ms_signal_handle(int sig);
void	ms_signal_handle_child(int sig);

// minishell_tokens.c
int		ms_regular_token_check(char *line);
int		ms_special_token_check(char *line, t_var *var);
bool	ms_token_counter(char *line, t_var *var);
bool	ms_token_filler(char *line, char **tokens);

// minishell_utils.c
int		ms_perror(char *err1, char *err2, char *err3, int err_no);
void	ms_clean(char **var_ptr);
void	ms_free_ptrs(t_var *var);
void	ms_heredoc_clean(void);
void	ms_exit(t_var *var, int exit_code);

// minishell_memory.c
void	*memlist_alloc(t_var *var, size_t size);
void	*memlist_add(t_var *var, void *ptr);
void	memlist_free_ptr(t_var *var, void *ptr);

// BUILTINS

// minishell_builtins_extra.c
void	ms_echo(char **tokens);
char	*getcwd_plus(t_var *var);
void	ms_pwd(t_var *var);
void	ms_exit_builtin(t_var *var);
// minishell_builtins_chdir.c
//static int	bad_status(int status);
//static void	cd_home(t_var *var);
//static void	cd_previous(t_var *var);
//static void	cd_todir(t_var *var, char **tokens)
void	ms_cd(t_var *var, char **tokens);
// minishell_builtins_vars.c
//static void	export_print(t_var *var);
//static void	export_add(t_var *var, char *token)
void	ms_export(t_var *var, char **tokens);
void	ms_unset(t_var *var, char **tokens);
void	ms_env(t_var *var);

// ENVIRONMENT VARIABLES

// minishell_env_init.c
void	modify_env_var(t_var *var, char *var_name, char *new_content);
//static bool	validate_shlvl(char *shlvl)
void	add_shlvl(t_var *var, char *shlvl);
void	create_env(t_var *var, char **env);
// minishell_env_helpers.c
void	varlist_clean(t_var	*var);
void	add_env_var(t_var *var, char *variable);
bool	find_env_var(t_var *var, char *var_name);
void	remove_env_var(t_var *var, char *var_name);
char	*get_env_var(t_var *var, char *variable);

// VARIABLE EXPANSION
// minishell_expansion.c
//static void token_size_logic(t_var *var, char *token, int *len, t_builder *b)
int		new_token_size(t_var *var, char *token);
//static void token_builder_logic(t_builder *b, char *token, t_var *var)
char	*token_builder(t_var *var, char *token);
bool	expand_cmd(t_var *var);
// minishell_expansion_helpers.c
int		var_len_diff(t_var *var, char *str);
char	*var_finder(t_var *var, char *str, char *new_token);

#endif
