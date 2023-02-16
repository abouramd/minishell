/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_table.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zasabri <zasabri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 14:05:23 by zasabri           #+#    #+#             */
/*   Updated: 2023/02/16 20:01:09 by zasabri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

t_list	*command_table(t_list *lexer)
{
	t_list		*cmd_table;
	t_vals		*first;
	t_cmd_list	*save;

	save = NULL;
	cmd_table = NULL;
	save = initilize_save(save);
	first = (t_vals *) lexer->content;
	while (first->token != V_EOF)
	{

		if (first->token = V_APP)
		{
			lexer = lexer->next;
			first = (t_vals *) lexer->content;
			if (first->token == V_STR)
				save->outfile = open(first->val, O_CREAT | O_RDWR | O_APPEND, 0777);
		}
		else if (first->token == V_RDIR)
		{
			lexer = lexer->next;
			first = (t_vals *) lexer->content;
			if (first->token == V_STR)
				save->outfile = open(first->val, O_TRUNC | O_CREAT | O_RDWR, 0777);
		}
		else if (first->token == V_LDIR)
		{
			lexer = lexer->next;
			first = (t_vals *) lexer->content;
			if (first->token == V_STR)
				save->infile = open(first->val, O_CREAT | O_RDWR, 0777);
		}
		else if (first->token == V_PIPE)
		{
			ft_lstadd_back(&cmd_table, ft_lstnew(save));
			save = init_content(save);
		}
		lexer = lexer->next;
		first = (t_vals *) lexer->content;
	}
	ft_lstadd_back(&cmd_table, ft_lstnew(save));
	return (cmd_table);
}