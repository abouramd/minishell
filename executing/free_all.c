/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouramd <abouramd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 18:21:04 by abouramd          #+#    #+#             */
/*   Updated: 2023/03/11 18:25:42 by abouramd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	free_cmd(t_cmd_list *list)
{
	if (list->cmd)
		ft_free(list->cmd);
	if (list->infile != 0)
		close(list->infile);
	if (list->outfile != 1)
		close(list->outfile);
	if (list->infile_name)
		free(list->infile_name);
	if (list->outfile_name)
		free(list->outfile_name);
	free(list);
}

void	free_all(t_data *f)
{
	t_cmd_list	*p;
	t_cmd_list	*tmp;

	p = f->list_of_cmd;
	tmp = f->list_of_cmd;
	while (tmp)
	{
		tmp = p;
		tmp = tmp->next;
		free_cmd(p);
		p = tmp;
	}
}

void	free_lexer(t_list *list)
{
	t_vals	*tmp;

	if (list)
	{
		if (list->next)
			free_lexer(list->next);
		tmp = (t_vals *)list->content;
		if (tmp)
		{
			if (tmp->val && tmp->e_token == V_STR)
				free(tmp->val);
			free(tmp);
		}
		free(list);
	}
}

void	free_hrd(t_here_doc *h)
{
	if (h)
	{
		if (h->next)
			free_hrd(h->next);
		if (h->infile != 0)
			close(h->infile);
		free(h);
	}
}
