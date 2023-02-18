/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zasabri <zasabri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 00:38:07 by zasabri           #+#    #+#             */
/*   Updated: 2023/02/18 02:28:04 by zasabri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

void	for_rderiction(t_vals *first, t_cmd_list *save, t_list **lexer)
{
	*lexer = (*lexer)->next;
	first = (t_vals *) (*lexer)->content;
	if (first->token == V_STR)
		save->outfile = open(first->val, O_CREAT | O_RDWR | O_TRUNC, 0777);
}

void	for_lderiction(t_vals *first, t_cmd_list *save, t_list **lexer)
{
	*lexer = (*lexer)->next;
	first = (t_vals *) (*lexer)->content;
	if (first->token == V_STR)
		save->infile = open(first->val, O_CREAT | O_RDWR, 0777);
}
void	for_append(t_vals *first, t_cmd_list *save, t_list **lexer)
{
	*lexer = (*lexer)->next;
	first = (t_vals *) (*lexer)->content;
	if (first->token == V_STR)
		save->outfile = open(first->val, O_CREAT | O_RDWR | O_APPEND, 0777);
}