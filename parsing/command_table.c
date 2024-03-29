/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_table.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouramd <abouramd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 14:05:23 by zasabri           #+#    #+#             */
/*   Updated: 2023/03/10 09:39:05 by abouramd         ###   ########.fr       */
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

static void	at_first(t_cmd_list **cmd_table, t_vals **first, t_list *lexer)
{
	*cmd_table = NULL;
	*first = (t_vals *)lexer->content;
}

static void	redirection(t_data **d, t_vals **first,
		t_cmd_list **save, t_list **lexer)
{
	if ((*first)->e_token == V_IN_RDIR || (*first)->e_token == V_OUT_RDIR
		|| (*first)->e_token == V_APP)
	{
		if ((*first)->e_token == V_IN_RDIR)
			for_input_redirection(*d, *first, *save, lexer);
		else if ((*first)->e_token == V_OUT_RDIR)
			for_out_redirection(*d, *first, *save, lexer);
		else if ((*first)->e_token == V_APP)
			for_append(*d, *first, *save, lexer);
	}
}

t_cmd_list	*command_table(t_data *d, t_here_doc *hrd, t_list *lexer)
{
	t_cmd_list	*cmd_table;
	t_vals		*first;
	t_cmd_list	*save;

	save = initilize_save();
	at_first(&cmd_table, &first, lexer);
	while (first->e_token != V_EOF)
	{
		if (first->e_token == V_STR)
			save->cmd = add_new(d, save->cmd, first->val);
		redirection(&d, &first, &save, &lexer);
		if (first->e_token == V_HDK)
			add_herdoc(&hrd, save, &lexer);
		else if (first->e_token == V_PIPE)
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
