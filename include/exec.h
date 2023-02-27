/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zasabri <zasabri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 03:38:12 by abouramd          #+#    #+#             */
/*   Updated: 2023/02/27 15:55:51 by zasabri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
#define EXEC_H

# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include <libft.h>
# include "include.h"
# include "readline.h"
# include <termios.h>







typedef struct s_pipe
{
	char	**path;
	char	*pathname;
	char	**cmd;
}			t_pipe;

typedef struct termios t_term;

typedef struct s_data
{
	t_cmd_list *list_of_cmd;
	char 	**my_env;
	int 	exit_status;
	struct sigaction old_sigint;
	struct sigaction old_sigquit;
	t_term old_tty;
	t_term new_tty;
	char	*pathname;
	char	**path;
}				t_data;

/* path fonction */
char	*creat_path(t_data *d);

char**    realloc_env(char **old_env, char *str);
void print_sort(char **s);
char **alloc_env(char **s);

/* print error */
void		ft_puterr(char *s, char *set, int n);

/* utile fonction */
char		*myjoin(char *s1, char *s2);
size_t		my_str_len(const char *s);
int			my_strstr(char *s, char *set);
int			ft_strcmp(char *s1, char *s2);


char	**split_path(t_data *d);
void	cmd_exec(t_data *d, t_pipe *f);

void ft_env_rm(char *elem, char ***my_env);
char *ft_find_env(char *elem, char **my_env);
void ft_env_add(char *elem, char ***env);

int builtins(t_data *f);

void	signal_handler(int signal);
char **alloc_env(char **s);
void rl_replace_line (const char *, int);

// builtins
void built_pwd(t_data *f);
void built_echo(t_data *f);
void built_cd(t_data *f);
void built_export(t_data *f);
void built_unset(t_data *f);
void built_env(t_data *f);
void built_exit(t_data *f);


void	pipeline(t_data *d);


#endif