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
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <sys/wait.h>
# include <string.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_manager
{
	void	*ptr;
	struct	s_manager *next;
}	t_manager;

typedef struct s_var
{
	_Bool	hdoc;
	int		*pipes;
	int		fd_in;
	int		fd_out;
	char	**paths;
	char	***cmds;
	t_manager	*memlist;
}			t_var;

// minishell_input.c
void	ft_open_heredoc(t_var *var, char *limit, size_t limit_len, char **env);
char	*ft_cmd_resolve(t_var *var, int i);
void	ft_start_args(t_var *var, char **av, int ac);

// minishell.c
void	ft_exit(t_var *var, int exit_code);
int		ft_perror(char *err1, char *err2, char *err3, int err_no);
int		ft_pipex(t_var *var, int end, char **env, int exit_code);

//mem_manager.c
void	*memlist_alloc(t_manager **head, size_t size);
void	*memlist_add(t_manager **head, void *ptr);
int		memlist_free_all(t_manager **head);
int		memlist_free_ptr(t_manager **head, void *ptr);

#endif
