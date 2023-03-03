/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouramd <abouramd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 00:38:07 by zasabri           #+#    #+#             */
/*   Updated: 2023/03/03 09:36:19 by abouramd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

void	for_out_redirection(t_vals *first, t_cmd_list *save, t_list **lexer)
{
	*lexer = (*lexer)->next;
	first = (t_vals *) (*lexer)->content;
	if (first->token == V_STR)
	{
		if (save->outfile > 0)
		{
			if (save->outfile != 1)
				close(save->outfile);	
			save->outfile = open(first->val, O_CREAT | O_WRONLY | O_TRUNC, 0644);
			if (save->outfile < 0)
			{
				save->outfile_errno = errno;
				save->outfile_name = ft_strdup(first->val);
			}
		}
	}
}

void	for_input_redirection(t_vals *first, t_cmd_list *save, t_list **lexer)
{
	*lexer = (*lexer)->next;
	first = (t_vals *) (*lexer)->content;
	if (first->token == V_STR)
	{
		if (save->infile >= 0)
		{
			if (save->infile != 0 && save->infile > 0)
				close(save->infile);
			save->infile = open(first->val, O_RDONLY, 0644);
			if (save->infile < 0)
			{
				save->infile_errno = errno;
				save->infile_name = ft_strdup(first->val);
			}
		}
	}
}

void	for_append(t_vals *first, t_cmd_list *save, t_list **lexer)
{
	*lexer = (*lexer)->next;
	first = (t_vals *) (*lexer)->content;
	if (first->token == V_STR)
	{
		if (save->outfile > 0)
		{
			if (save->outfile != 1 && save->outfile > 0)
				close(save->outfile);	
			save->outfile = open(first->val, O_CREAT | O_WRONLY | O_APPEND, 0644);
			if (save->outfile < 0)
			{
				save->outfile_errno = errno;
				save->outfile_name = ft_strdup(first->val);
			}
		}
	}
}
