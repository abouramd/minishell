/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouramd <abouramd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 01:20:12 by zasabri           #+#    #+#             */
/*   Updated: 2023/02/14 07:22:09 by abouramd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

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
