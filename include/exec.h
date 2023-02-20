/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouramd <abouramd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 03:38:12 by abouramd          #+#    #+#             */
/*   Updated: 2023/02/20 00:51:38 by abouramd         ###   ########.fr       */
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
#include "readline.h"
#include <termios.h>






typedef struct s_pipe
{
	char	**path;
	char	*pathname;
	char	**cmd;
}			t_pipe;



typedef struct termios t_term;

// typedef struct s_cmd_list
// {
// 	char	**cmd;
// 	int		infile;
// 	int		outfile;
// }	t_cmd_list;

typedef struct s_data
{
	t_cmd_list *list_of_cmd;
	char 	**my_env;
	char	**path;
	char	*pathname;
	int 	exit_status;
	struct sigaction old;
}	t_data;

/* path fonction */
char	*creat_path(t_data *d, t_pipe *f);
char		**split_path(char **env);


/* print error */
void		ft_puterr(char *s, char *set, int n);

/* utile fonction */
char		*myjoin(char *s1, char *s2);
size_t		my_str_len(const char *s);
void		ft_free(char **s);
int			my_strstr(char *s, char *set);
int			ft_strcmp(char *s1, char *s2);


char	**split_path(char **env);
void	cmd_exec(t_data *d, t_pipe *f);

void ft_env_rm(char *elem, char ***my_env);
char *ft_find_env(char *elem, char **my_env);
void ft_env_add(char *elem, char ***env);

int builtins(t_data *f);

void	signal_handler(int signal);
char **alloc_env(char **s);
void rl_replace_line (const char *, int);



#endif