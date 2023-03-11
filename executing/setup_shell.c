/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_shell.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouramd <abouramd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 18:19:00 by abouramd          #+#    #+#             */
/*   Updated: 2023/03/11 18:25:07 by abouramd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	print_start(void)
{
	ft_putstr_fd("\033[1;32m\n", 1);
	ft_putstr_fd("  ███╗   ███╗ ██╗ ███╗   ██╗ ██╗ \
███████╗ ██╗  ██╗ ███████╗ ██╗      ██╗     \n", 1);
	ft_putstr_fd("  ████╗ ████║ ██║ ████╗  ██║ ██║ \
██╔════╝ ██║  ██║ ██╔════╝ ██║      ██║     \n", 1);
	ft_putstr_fd("  ██╔████╔██║ ██║ ██╔██╗ ██║ ██║ \
███████╗ ███████║ █████╗   ██║      ██║     \n", 1);
	ft_putstr_fd("  ██║╚██╔╝██║ ██║ ██║╚██╗██║ ██║ \
╚════██║ ██╔══██║ ██╔══╝   ██║      ██║     \n", 1);
	ft_putstr_fd("  ██║ ╚═╝ ██║ ██║ ██║ ╚████║ ██║ \
███████║ ██║  ██║ ███████╗ ███████╗ ███████╗\n", 1);
	ft_putstr_fd("  ╚═╝     ╚═╝ ╚═╝ ╚═╝  ╚═══╝ ╚═╝ \
╚══════╝ ╚═╝  ╚═╝ ╚══════╝ ╚══════╝ ╚══════╝\n", 1);
	ft_putstr_fd("\033[0m\n", 1);
}

void	setup_shell(int ac, char **av, char **env, t_data *d)
{
	char	*tmp;
	char	pwd[PATH_MAX];

	(void)ac;
	tcgetattr(0, &d->new_tty);
	tcgetattr(0, &d->old_tty);
	d->new_tty.c_lflag &= ~ECHOCTL;
	tcsetattr(0, TCSANOW, &d->new_tty);
	sigaction(SIGINT, NULL, &d->old_sigint);
	sigaction(SIGQUIT, NULL, &d->old_sigquit);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, signal_handler);
	print_start();
	d->exit_status = 0;
	d->in_muti_pip = 0;
	d->my_env = alloc_env(env);
	getcwd(pwd, PATH_MAX - 1);
	tmp = ft_strtrim(av[0], "./");
	tmp = ft_free_joined("/", tmp, 0, 1);
	tmp = ft_free_joined(pwd, tmp, 0, 1);
	ft_env_add("SHELL", tmp, &d->my_env);
	free(tmp);
}
