/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zasabri <zasabri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 18:32:13 by zasabri           #+#    #+#             */
/*   Updated: 2023/02/04 18:32:13 by zasabri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/include.h"

void	signal_handler(int signal)
{
	if (signal == SIGINT)
		exit(0);
}

char	*add_str(char *str , char c)
{
	char *tmp = str;
	char *charachter;

	charachter = malloc(2);
	charachter[0] = c;
	charachter[1] = '\0';
	if(!str)
	{  
		str = charachter;
		free(charachter);
		return (str);
	}
	else
	{  
		str = ft_strjoin(str, charachter);
		free(tmp);
		free(charachter);
	}
	return(str);
}

t_vals	*fill_token(char *str, int v)
{
	t_vals	*token;

	token = malloc(sizeof(t_vals));
	token->val = str;
	token->token = v;
	return (token);
}

t_vals *set_tokens(t_lex *lexer)
{
	t_vals *token; 
	char *str;
	int flag = 1; 
	
	str = NULL;
	while (lexer->l && lexer->l == ' ')
	{
		lexer->nxt++;
		lexer->l = lexer->fill[lexer->nxt];
	}
	while((lexer->l != '\0')
		&& ((lexer->l != '|' && lexer->l != '>' && lexer->l != '<')
		|| flag != 0))
	{
		if (lexer->l == '\"')
			flag = 0;
		str = add_str(str, lexer->l);
		lexer->nxt++;
		lexer->l = lexer->fill[lexer->nxt];
	}
	token = malloc(sizeof(t_vals));
	if (str)
	{
		token->val = str;
		token->token = V_STR;
	}
	else
	{
		if(lexer->l == '>')
		{
			lexer->nxt++;
			lexer->l = lexer->fill[lexer->nxt];
			if (lexer->l == '>')
			{
				lexer->nxt++;
				lexer->l = lexer->fill[lexer->nxt];
				return fill_token(">>", V_APP);
			}
			return fill_token(">", V_RDIR);
		}   
		if (lexer->l == '<')
		{
			lexer->nxt++;
			lexer->l = lexer->fill[lexer->nxt];
			if(lexer->l == '<')
			{
				lexer->nxt++;
				lexer->l = lexer->fill[lexer->nxt];
				return fill_token("<<", V_HDK);
			}
			return fill_token("<", V_LDIR);
		}
		if(lexer->l == '|')
		{   
			lexer->nxt++;
			lexer->l = lexer->fill[lexer->nxt];
			return fill_token("|", V_PIPE);
		}
		else
			return fill_token("EOF", V_EOF);
	}
	return token;
}

t_list	*ft_lexer(char *rl)
{
	t_list	*lex;
	t_lex	analyze;
	t_vals	*token;

	analyze.fill = rl;
	analyze.nxt = 0;
	analyze.l = analyze.fill[analyze.nxt];
	lex = NULL;
	while (analyze.l != '\0')
	{
		token = set_tokens(&analyze);
	}
}

int	main(int ac, char **av, char **env)
{
	char	*rl;
	t_list	*lx;

	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
	while (1)
	{
		rl = readline(" minishell-1.0$ ");
		printf("%s\n", rl);
		add_history(rl);
		lx = ft_lexer(rl);
		if (!rl)
		{
			write(1, "exit\n", 5);
			exit(0);
		}
	}
}