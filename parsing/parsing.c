/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zasabri <zasabri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 02:49:34 by zasabri           #+#    #+#             */
/*   Updated: 2023/02/07 02:49:34 by zasabri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

void	signal_handler(int signal)
{
	if (signal == SIGINT)
		exit(0);
}

t_vals	*others(t_lex *lexer)
{
	if (lexer->l == '>')
	{
		go_next(lexer);
		if (lexer->l == '>')
		{
			go_next(lexer);
			return (initialize_token(">>", V_APP));
		}
		return (initialize_token(">", V_RDIR));
	}
	if (lexer->l == '<')
	{
		go_next(lexer);
		if (lexer->l == '<')
		{
			go_next(lexer);
			return (initialize_token("<<", V_HDK));
		}
		return (initialize_token("<", V_LDIR));
	}
	if (lexer->l == '|')
	{
		go_next(lexer);
		return (initialize_token("|", V_PIPE));
	}
	else
		return (initialize_token("EOF", V_EOF));
}

char	*add_str(char *str, char c)
{
	char	*charachter;
	char	*tmp;

	charachter = malloc(sizeof(char) * 2);
	charachter[0] = c;
	charachter[1] = '\0';
	if (!str)
	{
		str = charachter;
		return (str);
	}
	else
	{
		tmp = str;
		str = ft_strjoin(str, charachter);
		free(tmp);
		free(charachter);
	}
	return (str);
}

t_vals	*select_token(t_lex *lexer)
{
	t_vals *token;
	char *str;

	str = NULL;
	while (lexer->l && lexer->l == ' ')
	{
		lexer->nxt++;
		lexer->l = lexer->fill[lexer->nxt];
	}
	while (lexer->l)
	{
		if (lexer->l == '|' || lexer->l == '<' || lexer->l == '>')
			break;
		str = add_str(str, lexer->l);
		go_next(lexer);
	}
	if (str)
		token = initialize_token(str, V_STR);
	else
		token = others(lexer);
	//printf("Token: %d\nValues: %s\n", token->token, token->val);
	return (token);
}

t_list	*lexecal_analyzer(char *str)
{
	t_lex	lexer;
	t_vals	*token;
	t_list	*list;

	if (!str)
		return (NULL);
	initialize_lexer(&lexer, str);
	list = NULL;
	while (lexer.l != '\0')
	{
		token = select_token(&lexer);
		ft_lstadd_back(&list, ft_lstnew(token));
	}
	token = initialize_token(NULL, V_EOF);
	ft_lstadd_back(&list, ft_lstnew(token));
	// while (list)
	// {
	// 	t_vals *t = list->content; 
	// 	//printf("%s\n", t->val);
	// 	list = list->next;
	// }
	return (list);
}

int	main(int ac, char **av, char **env)
{
	char	*rl;
	t_list	*lexer;

	(void)av;
	(void)ac;
	(void)env;
	print_start();
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
	while (1)
	{
		rl = readline("\033[1;32mminishell-1.0$ \033[0m");
		if (!rl)
		{
			write(1, "exit\n", 5);
			exit(0);
		}
		add_history(rl);
		lexer = lexecal_analyzer(rl);
		if (all_is_good(lexer))
		{
			free(lexer);
			continue;
		}
		// if (!isValid(rl))
		// {
		// 	printf(" qout \" \' ");
		// 	continue;
		// }
		// printf("all is okay :)\n line => %s\n", rl);
	}
}
