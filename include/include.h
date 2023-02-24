/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   include.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouramd <abouramd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 18:34:05 by zasabri           #+#    #+#             */
/*   Updated: 2023/02/24 11:53:23 by abouramd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INCLUDE_H
# define INCLUDE_H

# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include "libft.h"
# include "set_val.h"
# include "lexer.h"
# include "command_list.h"

void		initialize_lexer(t_lex *lexer, char *str);
void		go_next(t_lex *lexer);
t_vals		*initialize_token(char *str, int v);
int			all_is_good(t_list *lexer);
char		*check_str(char *str);
char		*add_str(char *str, char c);
t_cmd_list	*initilize_save(void);
t_cmd_list	*command_table(t_list *lexer, int *exit_status);
int			isValid(char * s);
void		for_out_redirection(t_vals *first, t_cmd_list *save, t_list **lexer);
void		for_input_redirection(t_vals *first, t_cmd_list *save, t_list **lexer);
void		for_append(t_vals *first, t_cmd_list *save, t_list **lexer);
void		here_documents(t_list *tokens);
t_list		*lexecal_analyzer(char *str);
char		*remove_spaces(char *lexer);
void test(t_list *lexer);
// exec function
void	print_start(void);
void	for_herdoc(t_vals *first, t_cmd_list *save, t_list **lexer, int *exit_status);
char	*get_next_line(int fd);

#endif