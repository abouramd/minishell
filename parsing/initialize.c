/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zasabri <zasabri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 01:20:12 by zasabri           #+#    #+#             */
/*   Updated: 2023/02/16 14:33:39 by zasabri          ###   ########.fr       */
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

t_cmd_list	*initilize_save(t_cmd_list *save)
{
	save = malloc(sizeof(t_vals));
	save->infile = 0;
	save->outfile = 1;
	save->cmd = (char **)malloc(sizeof(char *) * 2);
	save->cmd[0] = NULL;
	save->cmd[1] = NULL;
	return (save);
}