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

# include "libft.h"
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <sys/wait.h>
# include <string.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_var
{
	_Bool	hdoc;
	char	*line;
	int		*pipes;
	int		fd_in;
	int		fd_out;
	char	**args;
	char	**env;
	char	**paths;
	char	***cmds;
	t_list	*token;
	char	pwd[4096];
	_Bool	s_quotes;
	_Bool	d_quotes;
}			t_var;

// minishell_input.c
int		ms_pipe_count(char const *s, char c);
char	*ft_cmd_resolve(t_var *var, int i);
_Bool	ms_quotes_check(t_var *var);
_Bool	ms_tokenize(t_var *var);
_Bool	ms_start_args(t_var *var, int cmd_count);
void	ms_start_mini(t_var *var, int cmd_count);

// minishell.c
int		ft_perror(char *err1, char *err2, char *err3, int err_no);
void	ft_clean(char **var_ptr);
void	ft_exit(t_var *var, int exit_code);
void	ft_exec_child(t_var *var, int i, int end);
_Bool	ms_exec_builtins(t_var *var, int i);
int		ms_pipex(t_var *var, int end, int exit_code);

#endif
