/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zasabri <zasabri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 02:49:34 by zasabri           #+#    #+#             */
/*   Updated: 2023/02/07 02:49:34 by zasabri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

t_vals	*others(t_lex *lexer)
{
	if (lexer->l == '|')
	{
		go_next(lexer);
		return (initialize_token(NULL, V_PIPE));
	}
	if (lexer->l == '<')
	{
		go_next(lexer);
		if (lexer->l == '<')
		{
			go_next(lexer);
			return (initialize_token(NULL, V_HDK));
		}
		return (initialize_token(NULL, V_IN_RDIR));
	}
	if (lexer->l == '>')
	{
		go_next(lexer);
		if (lexer->l == '>')
		{
			go_next(lexer);
			return (initialize_token(NULL, V_APP));
		}
		return (initialize_token(NULL, V_OUT_RDIR));
	}
	else
		return (initialize_token(NULL, V_EOF));
}

t_vals	*select_token(t_lex *lexer)
{
	t_vals *token;
	char *str;
	int i;

	str = NULL;
	while (lexer->l && lexer->l == ' ')
	{
		lexer->nxt++;
		lexer->l = lexer->fill[lexer->nxt];
	}
	i = 0;
	char c;
	while (lexer->l)
	{
		if ((lexer->l == '\"' || lexer->l == '\'') && i == 0)
		{
			i = 1;
			c = lexer->l;
		}
		else if (i == 1 && lexer->l == c)
			i = 0;
			if ((lexer->l == '|' || lexer->l == '<' || lexer->l == '>' || lexer->l == ' ') && i == 0)
				break;
			str = add_str(str, lexer->l);
			go_next(lexer);
	}
	if (str)
		token = initialize_token(str, V_STR);
	else
		token = others(lexer);
	return (token);
}

t_list	*lexecal_analyzer(char *str)
{
	t_lex	lexer;
	t_vals	*token;
	t_list	*list;

	if (!str)
		return (NULL);
	initialize_lexer(&lexer, str);
	list = NULL;
	while (lexer.l != '\0')
	{
		token = select_token(&lexer);
		ft_lstadd_back(&list, ft_lstnew(token));
	}
	token = initialize_token(NULL, V_EOF);
	ft_lstadd_back(&list, ft_lstnew(token));
	return (list);
}

// void print_tokens(t_vals *lexer)
// {
//         printf("value_of_token: %s (",lexer->val);
// 		if (lexer->token == 0)
// 			printf("str_token");
// 		else if (lexer->token == 1)
// 			printf("pipe_token");
// 		else if (lexer->token == 2)
// 			printf("append_token");
// 		else if (lexer->token == 3)
// 			printf("out_rederiction_token");
// 		else if (lexer->token == 4)
// 			printf("in_rederiction_token");
// 		else if (lexer->token == 5)
// 			printf("heredoce_token");
// 		else
// 			printf("end_of_file");
// 		printf(")\n");
// }

// void test(t_list *lexer)
// {
//     t_list *first = lexer;
//     while(first)
//     {
//         print_tokens((t_vals *) first->content);
//         first = first->next;
//     }
// }
