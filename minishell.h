/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miggarc2 <miggarc2@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 17:10:44 by miggarc2          #+#    #+#             */
/*   Updated: 2025/06/06 04:37:40 by frey-gal         ###   ########.fr       */
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

typedef struct s_varlist
{
	char	*var_name;
	char	*content;
	struct s_varlist	*next;
}	t_varlist;

typedef struct s_manager
{
	void	*ptr;
	struct	s_manager *next;
}	t_manager;

typedef struct s_var
{
	_Bool	hdoc;
	char	*line;
	int		*pipes;
	int		fd_in;
	int		fd_out;
	char	**tokens;
	char	**args;
	char	**env;
	char	**paths;
	char	***cmds;
	char	pwd[4096];
	int		exit_code;
	t_manager	*memlist;
	t_varlist	*varlist;
}			t_var;

// minishell_exec.c
void	ft_exec_child(t_var *var, int i, int end);
_Bool	ms_exec_builtins(t_var *var, int i);
int		ms_pipex(t_var *var, int end);

// minishell_init.c
char	*ft_cmd_resolve(t_var *var, int i);
_Bool	ms_start_args(t_var *var, int cmd_count);
void	ms_start_mini(t_var *var);
int		main(int ac, char **av, char **env);

// minishell_signals.c
void	ms_signal_handle(int sig);
void	ms_signal_handle_child(int sig);

// minishell_tokens.c
int		ms_special_token_len(char *line, int i);
int		ms_regular_token_len(char *line, int i);
int		ms_fill_tokens(char *line, char **tokens);
int		ms_token_counter(t_var *var);

// minishell_utils.c
int		ms_perror(char *err1, char *err2, char *err3, int err_no);
void	ms_clean(char **var_ptr);
void	ms_exit(t_var *var, int exit_code);

// minishell_memory.c
void	*memlist_alloc(t_manager **memlist, size_t size);
void	*memlist_add(t_manager **memlist, void *ptr);
int		memlist_free_all(t_manager **memlist);
int		memlist_free_ptr(t_manager **memlist, void *ptr);

// minishell_builtins.c
void	ft_echo(char **tokens);
int		ft_cd(t_var *var, char **tokens);
int		ft_pwd(t_var *var);
//void	ft_export(t_manager **memlist, char *tokens, t_varlist **varlist);
//void	ft_unset(t_manager **memlist, t_varlist **varlist);

// minishell_variables.c
void	add_var_node(t_var *var, char *var_name, char *content);
int		remove_var_node(t_var *var, char *var_name);
void	create_var_list(t_var *var, char **env);
char	*get_var(t_var *var, char *variable);
int		modify_var(t_var *var, char *var_name, char *new_content);

// temporary function for exiting program, gotta join it with miguels
//void	kill_and_exit(t_manager **memlist, int status, char *message);

#endif
