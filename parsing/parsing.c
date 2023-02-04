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

void	check_good(char **av, t_vals *seter)
{
	int	i;

	i = 0;
	while (av[i])
	{
		
	}
}

int	main(int ac, char **av, char **env)
{
	char	*rl;
	t_vals	seter;

	while (1)
	{
		rl = readline(" minishell-1.0$ ");
		add_history(rl);
		check_good(av, &seter);
		if (!rl)
		{
			write(1, "exit\n", 5);
			exit(0);
		}
	}
}