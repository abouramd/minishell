/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   include.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouramd <abouramd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 18:34:05 by zasabri           #+#    #+#             */
/*   Updated: 2023/03/12 10:50:32 by abouramd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INCLUDE_H
# define INCLUDE_H

# include "command_list.h"
# include "lexer.h"
# include "libft.h"
# include "set_val.h"
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <termios.h>

typedef struct termios	t_term;

typedef struct s_here_doc
{
	int					infile;
	struct s_here_doc	*next;
}						t_here_doc;

typedef struct s_data
{
	t_cmd_list			*list_of_cmd;
	char				**my_env;
	int					exit_status;
	int					kill_here;
	struct sigaction	old_sigint;
	struct sigaction	old_sigquit;
	t_term				old_tty;
	t_term				new_tty;
	char				*pathname;
	char				**path;
	int					in_muti_pip;
	int					ambiguous;
}						t_data;

void					initialize_lexer(t_lex *lexer, char *str);
void					go_next(t_lex *lexer);
t_vals					*initialize_token(char *str, int v);
char					*add_str(char *str, char c);
t_cmd_list				*initilize_save(void);
void					for_out_redirection(t_data *f, t_vals *first,
							t_cmd_list *save, t_list **lexer);
void					for_input_redirection(t_data *f, t_vals *first,
							t_cmd_list *save, t_list **lexer);
void					for_append(t_data *f, t_vals *first, t_cmd_list *save,
							t_list **lexer);
void					add_herdoc(t_here_doc **hrd, t_cmd_list *save,
							t_list **lexer);
t_list					*lexecal_analyzer(char *str);
void					print_start(void);
char					*get_next_line(int fd);
t_cmd_list				*command_table(t_data *d, t_here_doc *hrd,
							t_list *lexer);

char					**ft_expand_str(t_data *f, char *s);
char					*ft_expand_in_here_doc(t_data *f, char *s, int type);
char					*ft_replace_val(t_data *f, char *str,
							char *expanded_str, size_t *index);
t_here_doc				*open_here_doc(t_data *d, t_list *lexer);
void					for_herdoc(t_here_doc *hrd, t_data *d, t_vals *first,
							t_list **lexer);
int						check_herdoc_limits(t_list *lexer);
int						syntax_error(t_list *lexer);
int						pars(t_data *d, char *rl);

/* free function */
void					free_cmd(t_cmd_list *list);
void					free_all(t_data *f);
void					free_lexer(t_list *list);
void					free_hrd(t_here_doc *h);

#endif