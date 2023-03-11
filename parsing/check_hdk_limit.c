/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_hdk_limit.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zasabri <zasabri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 10:21:32 by zasabri           #+#    #+#             */
/*   Updated: 2023/03/11 10:41:56 by zasabri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

void	check_herdoc_limits(t_list *lexer)
{
	t_vals	*f;
	int		checker;

	checker = 0;
	f = (t_vals *)lexer->content;
	if (f->e_token == V_EOF)
		return ;
	while (f->e_token != V_EOF)
	{
		if (f->e_token == V_HDK)
			checker++;
		lexer = lexer->next;
		f = (t_vals *)lexer->content;
	}
	if (checker > 16)
	{
		printf("minishell: maximum here-document count exceeded\n");
		exit(2);
	}
}
