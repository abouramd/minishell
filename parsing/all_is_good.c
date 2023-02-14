/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all_is_good.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zasabri <zasabri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 09:19:23 by zasabri           #+#    #+#             */
/*   Updated: 2023/02/14 09:41:49 by zasabri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

int	all_is_good(t_list *lexer)
{
	t_vals	*first;
	t_vals	*second;
	char	*str;
	char	*save;

	str = NULL;
	first = (t_vals *) lexer->content;
	if (first->token == V_EOF)
		return (0);
	if (first->token == V_PIPE)
		return (printf("syntax error unexpected token `|'\n"));
	second = (t_vals *) lexer->next->content;
	while (first->token != V_EOF)
	{
		if ((first->token == V_APP || first->token == V_RDIR
			|| first->token == V_LDIR || first->token == V_HDK) && second->token != V_STR)
			return (printf("syntax error near unexpected token `%s'\n", second->val));
		if (first->token == V_STR)
		{
			save = first->val;
			if (str == NULL)
				return (printf("syntax error unexpected token `(null)'\n"));
			if (str != save)//drt hadi 7itach ila makanoch l qoutes rah ghaykon kaysawih but ila kano rah save ghaykono fih lqoutes so khass ytfreeya dak lfirst->val, you got me?
				free(save);
			first->val = str;//example for this : ila 3ndi $ls fa rah makayn mochkil but ila 3ndi $"ls" farah aykhssni gha $ls dakchi bach kan7at return d check str wa raha kathandli lblan d lquotes 7it ila str[strlen] == '\0' ayruterni null and ila returna null
			// fa ra ghayktb dak l message d syntax error + ktjoini liya gha string without qoutes. 
		}
		if (first->token != V_STR && second->token == V_PIPE)
			return (printf("syntax error near unexpected token `%s'\n", second->val));
		if (first->token == V_PIPE && second->token == V_EOF)
			return (printf("syntax error near unexpected token `%s'\n", second->val));
		if (second->token == V_EOF)
			break;
		lexer = lexer->next;
		first = (t_vals *) lexer->content;
		second = (t_vals *) lexer->next->content;
	}
	return (0);
}
