/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouramd <abouramd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 10:59:30 by abouramd          #+#    #+#             */
/*   Updated: 2023/03/01 14:34:20 by abouramd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"


void	signal_handler(int signum)
{
	if (signum == SIGINT)
	{
		g_d.exit_status = 1;
		// ft_putstr_fd("\033[1;31m", 1);
		ft_putstr_fd("\033[1;32m", 1);
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	signal_here_doc(int signum)
{
	if (signum == SIGINT)
	{
		ft_putchar_fd('\n', 2);
		exit(1);
	}
}

void	signal_exec(int signum)
{
	ft_putendl_fd("Quit: 3\n", 1);
	exit(128 + signum);
}
