/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_documents.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zasabri <zasabri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 02:15:07 by zasabri           #+#    #+#             */
/*   Updated: 2023/03/06 18:36:25 by zasabri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

static void	link_here_doc(t_here_doc **lst, t_here_doc *new)
{
	t_here_doc	*p;

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

static t_here_doc	*first_val_here_doc(void)
{
	t_here_doc	*here_doc;

	here_doc = malloc(sizeof(t_here_doc));
	here_doc->infile = 0;
	here_doc->next = NULL;
	return (here_doc);
}

t_here_doc	*open_here_doc(t_data *d, t_list *lexer)
{
	t_here_doc	*here_doc;
	t_here_doc	*tmp;
	t_vals		*first;
	int			save_exit;

	here_doc = NULL;
	tmp = NULL;
	first = (t_vals *)lexer->content;
	save_exit = d->exit_status;
	while (first->token != V_EOF)
	{
		if (first->token == V_IN_RDIR || first->token == V_OUT_RDIR
			|| first->token == V_APP)
			first = (t_vals *)lexer->content;
		else if (first->token == V_HDK)
		{
			tmp = first_val_here_doc();
			for_herdoc(tmp, d, first, &lexer);
			link_here_doc(&here_doc, tmp);
			tmp = NULL;
		}
		else if (first->token == V_PIPE)
			d->exit_status = 0;
		lexer = lexer->next;
		first = (t_vals *)lexer->content;
	}
	link_here_doc(&here_doc, tmp);
	d->exit_status = save_exit;
	return (here_doc);
}
