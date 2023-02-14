/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all_is_good.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zasabri <zasabri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 09:19:23 by zasabri           #+#    #+#             */
/*   Updated: 2023/02/14 08:19:55 by zasabri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

// char	*check_str(char *str)
// {
// 	int		i;
// 	char	*string;

// 	i = 0;
// 	string = NULL;
// 	while (str[i])
// 	{
// 		if (str[i] == '\"')
// 		{
// 			i += 1;
// 			while (str[i] && str[i] != '\"')
// 			{
// 				string = add_str(string, str[i]);
// 				i++;
// 			}
// 			if (str[i] == '\0')
// 				return (NULL);
// 			i++;
// 		}
// 		else if (str[i] == '\'')
// 		{	
// 			i++;
// 			while (str[i] && str[i] != '\'')
// 			{
// 				string = add_str(string, str[i]);
// 				i++;
// 			}
// 			if (str[i] == '\0')
// 				return (NULL);
// 			i++;
// 		}
// 		else
// 		{
// 			string = add_str(string, str[i]);
// 			i++;
// 		}
// 	}
// 	return (string);
// }
int	all_is_good(t_list *lexer)
{
	t_vals	*first;
	t_vals	*second;
	char	*str;

	str = NULL;
	first = (t_vals *) lexer->content;
	if (first->token == V_EOF)
		return (0);
	if (first->token == V_PIPE)
		return (printf("syntax error unexpected token `|'\n"));
	second = (t_vals *) lexer->next->content;
	while (first->token != V_EOF)
	{
		if ((first->token == V_APP || first->token == V_RDIR || first->token == V_LDIR || first->token == V_HDK) && second->token != V_STR)
			return (printf("syntax error near unexpected token `%s'\n", second->val));
		// if ((first->token == V_STR))
		// {
			
		// }
		if (first->token != V_STR && second->token == V_PIPE)
			return (printf("syntax error near unexpected token `%s'\n", second->val));
		if (first->token == V_PIPE && second->token == V_EOF)
			return (printf("syntax error near unexpected token `%s'\n", second->val));
		if (second->token == V_EOF)
			break;
		lexer = lexer->next;
		first = (t_vals *) lexer->content;
		second = (t_vals *) lexer->next->content;
	}
	return (0);
}
