/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zasabri <zasabri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 01:20:12 by zasabri           #+#    #+#             */
/*   Updated: 2023/02/07 02:06:17 by zasabri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/include.h"

void	initialize_lexer(t_lex *lexer, char *str)
{
	lexer->fill = str;
	lexer->nxt = 0;
	lexer->l = lexer->fill[lexer->nxt];
}

void	go_next(t_lex *lexer)
{
	lexer->nxt++;
	lexer->l = lexer->fill[lexer->nxt];
}

t_vals	*initialize_token(char *str, int v)
{
	t_vals	*token;

	token = malloc(sizeof(t_vals));
	token->token = v;
	token->val = str;
	return (token);
}
