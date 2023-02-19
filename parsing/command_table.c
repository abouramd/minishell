/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_table.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zasabri <zasabri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 14:05:23 by zasabri           #+#    #+#             */
/*   Updated: 2023/02/19 23:22:32 by zasabri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

t_list	*command_table(t_list *lexer)
{
	t_list		*cmd_table;
	t_vals		*first;
	t_cmd_list	*save;

	here_documents(lexer);
	save = NULL;
	cmd_table = NULL;
	save = initilize_save(save);
	first = (t_vals *) lexer->content;
	while (first->token != V_EOF)
	{
		if (first->token == V_STR)
			save->cmd = ft_split(first->val, ' ');
		else if (first->token == V_IN_RDIR)
		{
			for_input_redirection(first, save, &lexer);
			printf("%d\n", save->infile);
		}
		else if (first->token == V_OUT_RDIR)
		{
			for_out_redirection(first, save, &lexer);
			printf("%d\n", save->outfile);
		}
		else if (first->token == V_APP)
		{
			for_append(first, save, &lexer);
			printf("%d\n", save->outfile);
		}
		else if (first->token == V_PIPE)
		{
			ft_lstadd_back(&cmd_table, ft_lstnew(save));
			save = initilize_save(save);
		}
		lexer = lexer->next;
		first = (t_vals *) lexer->content;
	}
	ft_lstadd_back(&cmd_table, ft_lstnew(save));
	//t_list *tmp = cmd_table;
	// while (tmp != NULL)
	// {
	// 	t_cmd_list *y = tmp->content;
	// 	for (int j = 0;y->cmd[j];j++)
	// 		printf("cmd[%d] = %s\n", j,y->cmd[j]);
	// 	tmp = tmp->next;
	// }
	return (cmd_table);
}