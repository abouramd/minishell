/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zasabri <zasabri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 10:18:46 by zasabri           #+#    #+#             */
/*   Updated: 2023/03/11 10:44:30 by zasabri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

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

int	print_errors(int first, int second)
{
	if ((first == V_APP || first == V_IN_RDIR
			|| first == V_OUT_RDIR || first == V_HDK)
		&& (second != V_STR))
		return (1);
	if (first == V_PIPE && (second == V_PIPE || second == V_EOF))
		return (1);
	return (0);
}

int	syntax_error(t_list *lexer)
{
	t_vals	*f;
	t_vals	*s;

	f = (t_vals *)lexer->content;
	if (f->e_token == V_EOF)
		return (0);
	if (f->e_token == V_PIPE)
		return (err("syntax error near unexpected token `", f->val, 0));
	s = (t_vals *) lexer->next->content;
	while (f->e_token != V_EOF)
	{
		if (print_errors(f->e_token, s->e_token))
			return (err("syntax error near unexpected token`", s->val, 0));
		if (f->e_token == V_STR)
			if (check_str_look(f->val))
				return (1);
		if (s->e_token == V_EOF)
			break ;
		lexer = lexer->next;
		f = (t_vals *)lexer->content;
		s = (t_vals *)lexer->next->content;
	}
	return (0);
}
