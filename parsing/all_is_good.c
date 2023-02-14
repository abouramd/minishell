/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all_is_good.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zasabri <zasabri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 09:19:23 by zasabri           #+#    #+#             */
/*   Updated: 2023/02/14 02:41:35 by zasabri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/include.h"

int	all_is_good(t_list *lexer)
{
	t_vals	*first;
	t_vals	*second;

	first = (t_vals *) lexer->content;
	second = (t_vals *) lexer->next->content;
	if (first->token == V_PIPE) // ila pipe 3la lbdaya
		return (printf("syntax error unexpected token `|'\n"));
	while (first->token != V_EOF)
	{
		if (first->token == V_PIPE && second->token == V_RDIR)
		{
			first = (t_vals *) lexer->content;
			second = (t_vals *) lexer->next->content;
		}
		else if (first->token != V_STR && second->token != V_STR) // ila 3ndna matalan heredoc o wrah machi str_token
			return (printf("syntax error unexpected token `%s'\n", second->val));
		lexer = lexer->next;
		second = (t_vals *) lexer->content;
		if (first->token != V_EOF)
			second = (t_vals *) lexer->next->content;
	}
	if (first->token == V_RDIR) // ila 3la lbdaya kayn gir append wla redirection or ldirection
		return (printf("syntax error near unexpected token `newline'\n"));
	return (0);
}