/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_hdk_limit.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouramd <abouramd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 10:21:32 by zasabri           #+#    #+#             */
/*   Updated: 2023/03/12 10:05:17 by abouramd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

int	check_herdoc_limits(t_list *lexer)
{
	t_vals	*f;
	int		checker;

	checker = 0;
	f = (t_vals *)lexer->content;
	while (f->e_token != V_EOF)
	{
		if (f->e_token == V_HDK)
			checker++;
		lexer = lexer->next;
		f = (t_vals *)lexer->content;
	}
	if (checker > 16)
	{
		ft_putendl_fd("minishell: maximum here-document count exceeded", 2);
		exit(2);
	}
	return (0);
}
