/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_table.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zasabri <zasabri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 14:05:23 by zasabri           #+#    #+#             */
/*   Updated: 2023/03/06 18:36:15 by zasabri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

static void	link_back(t_cmd_list **lst, t_cmd_list *new)
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

char	**add_new(t_data *f, char **cmd, char *new)
{
	char	**new_cmd;
	size_t	i;
	char	**tmp;

	new_cmd = cmd;
	i = 0;
	tmp = ft_expand_str(f, new);
	if (!tmp)
		return (new_cmd);
	while (tmp && tmp[i])
	{
		cmd = new_cmd;
		new_cmd = ft_ultimate_join(cmd, tmp[i]);
		ft_free(cmd);
		free(tmp[i++]);
	}
	free(tmp);
	return (new_cmd);
}

t_cmd_list	*command_table(t_data *d, t_here_doc *hrd, t_list *lexer)
{
	t_cmd_list	*cmd_table;
	t_vals		*first;
	t_cmd_list	*save;

	save = NULL;
	cmd_table = NULL;
	save = initilize_save();
	first = (t_vals *)lexer->content;
	while (first->token != V_EOF)
	{
		if (first->token == V_STR)
			save->cmd = add_new(d, save->cmd, first->val);
		else if (first->token == V_IN_RDIR)
			for_input_redirection(d, first, save, &lexer);
		else if (first->token == V_OUT_RDIR)
			for_out_redirection(d, first, save, &lexer);
		else if (first->token == V_APP)
			for_append(d, first, save, &lexer);
		else if (first->token == V_HDK)
			add_herdoc(&hrd, save, &lexer);
		else if (first->token == V_PIPE)
		{
			link_back(&cmd_table, save);
			d->exit_status = 0;
			save = initilize_save();
		}
		lexer = lexer->next;
		first = (t_vals *)lexer->content;
	}
	d->exit_status = 0;
	link_back(&cmd_table, save);
	return (cmd_table);
}
