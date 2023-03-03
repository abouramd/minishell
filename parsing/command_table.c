/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_table.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouramd <abouramd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 14:05:23 by zasabri           #+#    #+#             */
/*   Updated: 2023/03/03 11:47:57 by abouramd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

void	link_back(t_cmd_list **lst, t_cmd_list *new)
{
	t_cmd_list	*p;

	if (lst)
	{
		if (!(*lst))
		{
			*lst = new;
		}
		else
		{
			p = *lst;
			while (p->next)
				p = p->next;
			p->next = new;
		}
	}
}

int	ambiguous_check(t_vals *first, t_list *lexer)
{
	int	i = 0;
	
	//printf("First: %s\n", first->val);
	lexer = lexer->next;
	first = (t_vals *)lexer->content;
	//printf("[%s]\n", first->val);
	if (first->token == V_STR)
	{
		while (first->val[i])
		{
			if (first->val[i] == ' ')
				return (1);
			i++;
		}
	}
	return (0);
}

char ** add_new(char **cmd, char *new)
{
	char **new_cmd;

	new_cmd = ft_ultimate_join(cmd, new);
	if (!new_cmd)
	    return (cmd);
	if (cmd)
		ft_free(cmd);
	return (new_cmd);
}

t_cmd_list	*command_table(t_data *d, t_list *lexer)
{
	t_cmd_list	*cmd_table;
	t_vals		*first;
	t_cmd_list	*save;

	save = NULL;
	cmd_table = NULL;
	save = initilize_save();
	first = (t_vals *) lexer->content;
	while (first->token != V_EOF)
	{
		if (first->token == V_STR)
			save->cmd = add_new(save->cmd, first->val);
		else if (first->token == V_IN_RDIR)
		{
			if (!ambiguous_check(first, lexer))
				for_input_redirection(first, save, &lexer);
			else
				printf("minishell: ambiguous redirect\n");
		}
		else if (first->token == V_OUT_RDIR)
		{
			//if (!ambiguous_check(first, lexer))
				for_out_redirection(first, save, &lexer);
		}
		else if (first->token == V_APP)
		{
			//if (!ambiguous_check(first, lexer))
				for_append(first, save, &lexer);
		}
		else if (first->token == V_HDK)
			for_herdoc(d, first, save, &lexer);
		else if (first->token == V_PIPE)
		{
			link_back(&cmd_table, save);
			save = initilize_save();
		}
		lexer = lexer->next;
		first = (t_vals *) lexer->content;
	}
	link_back(&cmd_table, save);
	return (cmd_table);
}