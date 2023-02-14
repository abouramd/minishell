/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all_is_good.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouramd <abouramd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 09:19:23 by zasabri           #+#    #+#             */
/*   Updated: 2023/02/14 07:22:05 by abouramd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

int	all_is_good(t_list *lexer)
{
	t_vals	*first;
	t_vals	*second;

	first = (t_vals *) lexer->content;
	if (first->token == V_EOF)
		return (0);
	if (first->token == V_PIPE) // ila pipe 3la lbdaya
		return (printf("syntax error unexpected token `|'\n"));
	second = (t_vals *) lexer->next->content;
	while (second->token != V_EOF)
	{
		// if (first->token == V_PIPE && second->token == V_RDIR)
		// {
		// }
		// else if (first->token != V_STR && second->token != V_STR) // ila 3ndna matalan heredoc o wrah machi str_token
		// 	return (printf("syntax error unexpected token `%s'\n", second->val));
		if ((first->token == V_APP || first->token == V_RDIR || first->token == V_LDIR || first->token == V_HDK) && second->token != V_STR)
			return (printf("syntax error unexpected token `%s'\n", second->val));
		if (first->token != V_STR && second->token == V_PIPE)
			return (printf("syntax error unexpected token `%s'\n", second->val));
		// second = (t_vals *) lexer->content;
		// if (first->token != V_EOF)
		// 	second = (t_vals *) lexer->next->content;
		lexer = lexer->next;
		first = (t_vals *) lexer->content;
		second = (t_vals *) lexer->next->content;
	}
	// if (first->token == V_RDIR) // ila 3la lbdaya kayn gir append wla redirection or ldirection
	// 	return (printf("syntax error near unexpected token `newline'\n"));
	return (0);
}

	/*
	* ila kat 3ndk append wla redirection okayn 9damha lfile rah katdoz 3adi o kat9ra mn stdin 
	* example : "> filename" or ">> filename"
	* had l error kaytl3 mli katkon append wla redirection oma9damha walo ola f7alat ila kant 9damhom chi token akhra b7al "|" ola "<<"
	* ya3ni mli gatl9a ">>" ola ">"  ola "<" ola "<<" o9damha chi 7aja mn ghir string dik sa3a ghadi ttl3 error 7it mkaynch lfile
	*/