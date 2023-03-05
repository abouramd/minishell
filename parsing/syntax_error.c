/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouramd <abouramd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 10:18:46 by zasabri           #+#    #+#             */
/*   Updated: 2023/03/05 13:31:22 by abouramd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

static void	puterr_for_parser(char *error, char *arg, int n)
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
			{
				puterr_for_parser("syntax error near unexpected token `", "\'", 0);
				return (1);
			}
		}
		else if (str[i] == '\"')
		{
			i++;
			while (str[i] && str[i] != '\"')
				i++;
			if (!str[i])
			{
				puterr_for_parser("syntax error near unexpected token `", "\"", 0);
				return (1);
			}
		}
		i++;
	}
	return (0);
}

int	syntax_error(t_list *lexer)
{
	t_vals	*first;
	t_vals	*second;

	first = (t_vals *)lexer->content;
	if (first->token == V_EOF)
		return (0);
	if (first->token == V_PIPE)
	{
		puterr_for_parser("syntax error near unexpected token `", first->val, 0);
		return (1);
	}
	second = (t_vals *) lexer->next->content;
	while (first->token != V_EOF)
	{
		if ((first->token == V_APP || first->token == V_IN_RDIR
			|| first->token == V_OUT_RDIR || first->token == V_HDK) && (second->token != V_STR))
		{
			//printf("hi: token->[%d], value->[%s] | second token->[%d]\n", first->token, first->val, second->token);
			puterr_for_parser("syntax error near unexpected token `", second->val, 0);
			return (1);
		}
		if (first->token == V_STR)
		{
			//printf("hi: token->[%d], value->[%s] | second token->[%d]\n", first->token, first->val, second->token);
			if (check_str_look(first->val))
				return (1);
		}
		if (first->token == V_PIPE && (second->token == V_EOF || second->token == V_PIPE))
		{
			//printf("hi: token->[%d], value->[%s] | second token->[%d]\n", first->token, first->val, second->token);
			puterr_for_parser("syntax error near unexpected token `", first->val, 0);
			return (1);
		}
		if (second->token == V_EOF)
			break;
		lexer = lexer->next;
		first = (t_vals *)lexer->content;
		second = (t_vals *)lexer->next->content;
	}
	return (0);
}
