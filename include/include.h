/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   include.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouramd <abouramd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 18:34:05 by zasabri           #+#    #+#             */
/*   Updated: 2023/02/14 07:21:59 by abouramd         ###   ########.fr       */
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

void	initialize_lexer(t_lex *lexer, char *str);
void	go_next(t_lex *lexer);
t_vals	*initialize_token(char *str, int v);
int		all_is_good(t_list *lexer);




// exec function
void print_start(void);

#endif