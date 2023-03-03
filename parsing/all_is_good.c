/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all_is_good.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zasabri <zasabri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 09:19:23 by zasabri           #+#    #+#             */
/*   Updated: 2023/03/03 14:34:45 by zasabri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

// char	*for_expand(char *str)
// {
// 	int i = 0;
// 	if (save->cmd)
// 	{
// 		char *ptr;
		
// 		while (save->cmd[i])
// 		{
// 			if ((ft_strnstr(save->cmd[i], "$", ft_strlen(save->cmd[i]))))
// 					save->cmd[i] = replace_the_value(save->cmd[i], print_env_content(save->cmd[i], d.my_env));
// 			i++;
// 		}
// 		ptr = save->cmd[i];
// 		free(ptr);
// 	}
// }

char	*replace_the_value(char	*cmd, char *str)
{
	if (str)
		cmd = str;
	return (cmd);
}

int	all_is_good(t_list *lexer, char **env)
{
	t_vals	*first;
	t_vals	*second;
	t_lex	check;
	char	*str;
	char	*save;

	check.v = 0;
	str = NULL;
	first = (t_vals *) lexer->content;
	if (first->token == V_EOF)
		return (0);
	if (first->token == V_PIPE)
		return (printf("syntax error unexpected token `|'\n"));
	second = (t_vals *) lexer->next->content;
	int	size = ft_lstsize(lexer);
	//printf("%d->\n", size);
	while (first->token != V_EOF)
	{
		if ((first->token == V_APP || first->token == V_OUT_RDIR
			|| first->token == V_IN_RDIR || first->token == V_HDK) && second->token != V_STR)
			return (printf("syntax error near unexpected token `%s'\n", second->val));
		// printf("%d", size);
		if (first->token == V_HDK && size > 4)
		{
			lexer = lexer->next->next;
			first = (t_vals *) lexer->next->content;
			second = (t_vals *) lexer->next->next->content;
		}
		if (first->token == V_HDK && size <= 4)
			break;
		if (first->token == V_STR)
		{
			save = first->val;
			str = check_str(first->val, &check);
			if (!str)
				return (printf("syntax error unexpected token `(null)'\n"));
			if (str != save)
				free(save);
			//printf("[%d]\n", first->token);
			if (ft_strnstr(str, "$", ft_strlen(str)) && (check.v == 0 || check.v == 5))
				str = replace_the_value(str, print_env_content(str, env));
			first->val = str;
		}
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
