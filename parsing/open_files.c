/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zasabri <zasabri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 00:38:07 by zasabri           #+#    #+#             */
/*   Updated: 2023/02/20 02:55:41 by zasabri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

void	for_out_redirection(t_vals *first, t_cmd_list *save, t_list **lexer)
{
	*lexer = (*lexer)->next;
	first = (t_vals *) (*lexer)->content;
	if (first->token == V_STR)
		save->outfile = open(first->val, O_CREAT | O_WRONLY | O_TRUNC, 0644);
}

void	for_input_redirection(t_vals *first, t_cmd_list *save, t_list **lexer)
{
	char	*str;
	
	*lexer = (*lexer)->next;
	first = (t_vals *) (*lexer)->content;
	if (first->token == V_STR)
	{
		str = remove_spaces(first->val);
		save->infile = open(str, O_RDONLY, 0644);
	}
}
void	for_append(t_vals *first, t_cmd_list *save, t_list **lexer)
{
	*lexer = (*lexer)->next;
	first = (t_vals *) (*lexer)->content;
	if (first->token == V_STR)
		save->outfile = open(first->val, O_CREAT | O_WRONLY | O_APPEND, 0644);
}
