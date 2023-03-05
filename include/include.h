/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   include.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouramd <abouramd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 18:34:05 by zasabri           #+#    #+#             */
/*   Updated: 2023/03/04 19:05:06 by abouramd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INCLUDE_H
# define INCLUDE_H

# include <stdlib.h>
# include <fcntl.h>
# include <errno.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include "libft.h"
# include "set_val.h"
# include "lexer.h"
# include "command_list.h"
#include <termios.h>

typedef struct termios t_term;

typedef struct s_data
{
	t_cmd_list *list_of_cmd;
	char 	**my_env;
	int 	exit_status;
	int		kill_here;
	struct sigaction old_sigint;
	struct sigaction old_sigquit;
	t_term old_tty;
	t_term new_tty;
	char	*pathname;
	char	**path;
	char    *tty;
	int ambiguous;
}				t_data;

void		initialize_lexer(t_lex *lexer, char *str);
void		go_next(t_lex *lexer);
t_vals		*initialize_token(char *str, int v);
int			all_is_good(t_list *lexer, char **env);
char		*check_str(char *str, t_lex *check);
char		*add_str(char *str, char c);
t_cmd_list	*initilize_save(void);
int			isValid(char * s);
void		for_out_redirection(t_data *f, t_vals *first, t_cmd_list *save, t_list **lexer);
void		for_input_redirection(t_data *f, t_vals *first, t_cmd_list *save, t_list **lexer);
void		for_append(t_data *f, t_vals *first, t_cmd_list *save, t_list **lexer);
void		here_documents(t_list *tokens);
t_list		*lexecal_analyzer(char *str);
char		*remove_spaces(char *lexer);
void test(t_list *lexer);
// exec function
void	print_start(void);
char	*get_next_line(int fd);
t_cmd_list	*command_table(t_data *f,t_list *lexer);
void	for_herdoc(t_data *d, t_vals *first, t_cmd_list *save, t_list **lexer);
char		*print_env_content(char *line, char **env);
char	**ft_expand_str(t_data *f, char *s);
char	*ft_expand_in_here_doc(t_data *f, char *s, int type);
char	*ft_expand_in_red(t_data *f, char *s);

#endif