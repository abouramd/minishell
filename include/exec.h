/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouramd <abouramd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 03:38:12 by abouramd          #+#    #+#             */
/*   Updated: 2023/03/12 10:50:15 by abouramd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "get_next_line.h"
# include "include.h"
# include "readline.h"
# include <dirent.h>
# include <limits.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

/*
*	executing
*/

/* globale var */
t_data	g_d;

/* my define */
# define DEFIN_ENV 1
# define APPAND_ENV 2

/* print error */
void	ft_puterr(char *s, char *set, int n);

/* function work with path */
char	**split_path(t_data *d, int *choose);
char	*creat_path(t_data *d);

/* function work with env */
void	ft_env_add(char *identifier, char *value, char ***env);
char	*ft_find_env(char *elem, char **my_env);
void	ft_env_rm(char *elem, char ***my_env);
char	**alloc_env(char **s);
char	**realloc_env(char **old_env, char *str);
void	print_sort(char **s, int fd);

/* signal handler */
void	signal_handler(int signum);
void	signal_here_doc(int signum);

/* executing a cmd */
void	exec_cmd(t_data *d);

/* working with here_doc */
char	*get_next_line(int fd);

/* manage fd */
void	dup_fd(int fd, int file_errno, char *file_name, int new_fd);
void	give_fd(t_cmd_list *f, int infile, int outfile);
void	close_useless_fd(t_cmd_list *cmd, int prev_fd);
void	close_fd_in_parent(t_data *d);

/* builtins */
int		builtins(t_data *f);
void	built_pwd(t_data *f);
void	built_echo(t_data *f);
void	built_cd(t_data *f);
void	built_export(t_data *f);
void	built_unset(t_data *f);
void	built_env(t_data *f);
void	built_exit(t_data *f);

/* readline function */
void	rl_replace_line(const char *s, int n);

/* setup shell */
void	setup_shell(int ac, char **av, char **env, t_data *d);

#endif