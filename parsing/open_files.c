/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouramd <abouramd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 00:38:07 by zasabri           #+#    #+#             */
/*   Updated: 2023/03/10 09:20:23 by abouramd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

char	**m_file(t_data *f, int file_fd, char *file_name, char *val)
{
	char	**name;

	f->ambiguous = 0;
	if (file_fd != 1 && file_fd != 0)
		close(file_fd);
	if (file_name)
		free(file_name);
	name = ft_expand_str(f, val);
	if (!name || !name[0] || name[1])
		f->ambiguous = 1;
	return (name);
}

void	for_out_redirection(t_data *f, t_vals *first, t_cmd_list *save,
		t_list **lexer)
{
	char	**name;

	*lexer = (*lexer)->next;
	first = (t_vals *)(*lexer)->content;
	if (first->token == V_STR && save->outfile > 0 && save->infile >= 0)
	{
		name = m_file(f, save->outfile, save->outfile_name, first->val);
		if (!f->ambiguous)
		{
			save->outfile = open(name[0], O_CREAT | O_WRONLY | O_TRUNC, 0644);
			if (save->outfile < 0)
			{
				save->outfile_errno = errno;
				save->outfile_name = ft_strdup(name[0]);
			}
			ft_free(name);
		}
		else
		{
			ft_free(name);
			save->outfile = -1;
			save->outfile_errno = 300;
			save->outfile_name = ft_strdup(first->val);
		}
	}
}

void	for_input_redirection(t_data *f, t_vals *first, t_cmd_list *save,
		t_list **lexer)
{
	char	**name;

	*lexer = (*lexer)->next;
	first = (t_vals *)(*lexer)->content;
	if (first->token == V_STR && save->outfile > 0 && save->infile >= 0)
	{
		name = m_file(f, save->infile, save->infile_name, first->val);
		if (!f->ambiguous)
		{
			save->infile = open(name[0], O_RDONLY, 0644);
			if (save->infile < 0)
			{
				save->infile_errno = errno;
				save->infile_name = ft_strdup(name[0]);
			}
			ft_free(name);
		}
		else
		{
			ft_free(name);
			save->outfile = -1;
			save->outfile_errno = 300;
			save->outfile_name = ft_strdup(first->val);
		}
	}
}

void	for_append(t_data *f, t_vals *first, t_cmd_list *s, t_list **lexer)
{
	char	**name;

	*lexer = (*lexer)->next;
	first = (t_vals *)(*lexer)->content;
	if (first->token == V_STR && s->outfile > 0 && s->infile >= 0)
	{
		name = m_file(f, s->outfile, s->outfile_name, first->val);
		if (!f->ambiguous)
		{
			s->outfile = open(name[0], O_CREAT | O_WRONLY | O_APPEND, 0644);
			if (s->outfile < 0)
			{
				s->outfile_errno = errno;
				s->outfile_name = ft_strdup(name[0]);
			}
			ft_free(name);
		}
		else
		{
			ft_free(name);
			s->outfile = -1;
			s->outfile_errno = 300;
			s->outfile_name = ft_strdup(first->val);
		}
	}
}

void	add_herdoc(t_here_doc **hrd, t_cmd_list *save, t_list **lexer)
{
	t_vals	*first;

	*lexer = (*lexer)->next;
	first = (t_vals *)(*lexer)->content;
	if (first->token == V_STR && (*hrd))
	{
		if (save->outfile > 0 && save->infile >= 0)
		{
			if (save->infile != 0)
				close(save->infile);
			save->infile = (*hrd)->infile;
		}
		else
			close((*hrd)->infile);
		(*hrd)->infile = 0;
		(*hrd) = (*hrd)->next;
	}
}
