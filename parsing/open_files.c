/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouramd <abouramd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 00:38:07 by zasabri           #+#    #+#             */
/*   Updated: 2023/03/04 19:26:03 by abouramd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

void	for_out_redirection(t_data *f, t_vals *first, t_cmd_list *save,
		t_list **lexer)
{
	char	*name;

	*lexer = (*lexer)->next;
	first = (t_vals *)(*lexer)->content;
	if (first->token == V_STR)
	{
		if (save->outfile > 0)
		{
			if (save->outfile != 1)
				close(save->outfile);
			f->ambiguous = 0;
			name = ft_expand_in_red(f, first->val);
			if (!f->ambiguous)
			{
				save->outfile = open(name, O_CREAT | O_WRONLY | O_TRUNC,
						0644);
				if (save->outfile < 0)
				{
					save->outfile_errno = errno;
					save->outfile_name = name;
				}
			}
			else
			{
				free(name);
				save->outfile = -1;
				save->outfile_errno = 300;
				save->outfile_name = ft_strdup(first->val);
			}
		}
	}
}

void	for_input_redirection(t_data *f, t_vals *first, t_cmd_list *save,
		t_list **lexer)
{
	*lexer = (*lexer)->next;
	first = (t_vals *)(*lexer)->content;
	if (first->token == V_STR)
	{
		if (save->infile >= 0)
		{
			if (save->infile != 0 && save->infile > 0)
				close(save->infile);
			f->ambiguous = 0;
			char *name = ft_expand_in_red(f, first->val);
			if (!f->ambiguous)
			{
				save->infile = open(name, O_RDONLY, 0644);
				if (save->infile < 0)
				{
					save->infile_errno = errno;
					save->infile_name = name;
				}
			}
			else
			{
				free(name);
				save->outfile = -1;
				save->outfile_errno = 300;
				save->outfile_name = ft_strdup(first->val);
			}
		}
	}
}

void	for_append(t_data *f, t_vals *first, t_cmd_list *save, t_list **lexer)
{
	*lexer = (*lexer)->next;
	first = (t_vals *)(*lexer)->content;
	if (first->token == V_STR)
	{
		if (save->outfile > 0)
		{
			if (save->outfile != 1 && save->outfile > 0)
				close(save->outfile);
			f->ambiguous = 0;
			char *name = ft_expand_in_red(f, first->val);
			if (!f->ambiguous)
			{
				save->outfile = open(name, O_CREAT | O_WRONLY | O_APPEND,
						0644);
				if (save->outfile < 0)
				{
					save->outfile_errno = errno;
					save->outfile_name = name;
				}
			}
			else
			{
				free(name);
				save->outfile = -1;
				save->outfile_errno = 300;
				save->outfile_name = ft_strdup(first->val);
			}
		}
	}
}
