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
	int		*pipes;
	int		fd_in;
	int		fd_out;
	char	**av;
	char	**env;
	char	**paths;
	char	***cmds;
	t_list	*token;
	char	pwd[4096];
}			t_var;

// minishell_input.c
void	ft_start_mini(t_var *var);
char	*ft_cmd_resolve(t_var *var, int i);
void	ft_start_args(t_var *var, char **av, int ac);

// minishell.c
void	ft_clean(char **var_ptr);
void	ft_exit(t_var *var, int exit_code);
int		ft_perror(char *err1, char *err2, char *err3, int err_no);
int		ft_pipex(t_var *var, int end, char **env, int exit_code);

#endif
