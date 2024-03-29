/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_documents.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouramd <abouramd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 02:15:07 by zasabri           #+#    #+#             */
/*   Updated: 2023/03/13 11:19:30 by abouramd         ###   ########.fr       */
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

static void	at_first(t_here_doc **here_doc, t_here_doc **tmp,
		t_vals **first, t_list *lexer)
{
	*here_doc = NULL;
	*tmp = NULL;
	*first = (t_vals *)lexer->content;
}

t_here_doc	*open_here_doc(t_data *d, t_list *lexer)
{
	t_here_doc	*here_doc;
	t_here_doc	*tmp;
	t_vals		*first;

	at_first(&here_doc, &tmp, &first, lexer);
	d->save_status = d->exit_status;
	while (first->e_token != V_EOF)
	{
		if (first->e_token == V_IN_RDIR || first->e_token == V_OUT_RDIR
			|| first->e_token == V_APP)
			first = (t_vals *)lexer->content;
		else if (first->e_token == V_HDK)
		{
			tmp = first_val_here_doc();
			for_herdoc(tmp, d, first, &lexer);
			link_here_doc(&here_doc, tmp);
		}
		else if (first->e_token == V_PIPE)
			d->exit_status = 0;
		lexer = lexer->next;
		first = (t_vals *)lexer->content;
	}
	d->exit_status = d->save_status;
	return (here_doc);
}
