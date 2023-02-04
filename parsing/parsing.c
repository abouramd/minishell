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

void signal_handler(int signal)
{
    if (signal == SIGINT)
        exit(0);
}

t_list	*ft_lexer(char *rl)
{
	t_list	*lex;
	t_lex	analyze;
	t_vals	*token;

	analyze.fill = rl;
	analyze.nxt = 0;
	analyze.l = analyze.fill[analyze.nxt];
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
		add_history(rl);
		lx = ft_lexer(rl);
		if (!rl)
		{
			write(1, "exit\n", 5);
			exit(0);
		}
	}
}