/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouramd <abouramd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 10:18:46 by zasabri           #+#    #+#             */
/*   Updated: 2023/03/10 09:38:35 by abouramd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

static int	err(char *error, char *arg, int n)
{
	ft_putstr_fd("minishell: ", 2);
	if (error)
		ft_putstr_fd(error, 2);
	if (arg)
		ft_putstr_fd(arg, 2);
	else
		ft_putstr_fd("newline", 2);
	ft_putstr_fd("\'\n", 2);
	if (n != 0)
		exit(n);
	return (1);
}

int	for_str_look_errors(char *c)
{
	err("syntax error near unexpected token `", c, 0);
	return (1);
}

static int	check_str_look(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'')
		{
			i++;
			while (str[i] && str[i] != '\'')
				i++;
			if (!str[i])
				return (for_str_look_errors("\'"));
		}
		else if (str[i] == '\"')
		{
			i++;
			while (str[i] && str[i] != '\"')
				i++;
			if (!str[i])
				return (for_str_look_errors("\""));
		}
		i++;
	}
	return (0);
}

int	syntax_error(t_list *lexer)
{
	t_vals	*first;
	t_vals	*second;
	int		hdk_nb;

	hdk_nb = 0;
	first = (t_vals *)lexer->content;
	if (first->e_token == V_EOF)
		return (0);
	if (first->e_token == V_PIPE)
		return (err("syntax error near unexpected token `", first->val, 0));
	second = (t_vals *) lexer->next->content;
	while (first->e_token != V_EOF)
	{
		if (first->e_token == V_HDK)
			hdk_nb++;
		if ((first->e_token == V_APP || first->e_token == V_IN_RDIR
				|| first->e_token == V_OUT_RDIR || first->e_token == V_HDK)
			&& (second->e_token != V_STR))
			return (err("syntax error near unexpected token`", second->val, 0));
		if (first->e_token == V_STR)
		{
			if (check_str_look(first->val))
				return (1);
		}
		if (first->e_token == V_PIPE && (second->e_token == V_EOF || second->e_token == V_PIPE))
			return (err("syntax error near unexpected token `", first->val, 0));
		if (second->e_token == V_EOF)
			break ;
		lexer = lexer->next;
		first = (t_vals *)lexer->content;
		second = (t_vals *)lexer->next->content;
	}
	if (hdk_nb > 16)
		err("maximum here-document count exceeded ", "`<<", 2);
	return (0);
}
