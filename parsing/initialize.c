/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zasabri <zasabri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 01:20:12 by zasabri           #+#    #+#             */
/*   Updated: 2023/02/12 04:30:49 by zasabri          ###   ########.fr       */
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

t_vals	*initialize_token(char *str, int type)
{
	t_vals	*token;

	token = malloc(sizeof(t_vals));
	if (!token)
		return (NULL);
	token->token = type;
	token->val = str;
	return (token);
}
