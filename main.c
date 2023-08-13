/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouramd <abouramd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 18:22:54 by abouramd          #+#    #+#             */
/*   Updated: 13/08/2023 05:07:23 PM abouramd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

t_data	g_d;


void	signal_handler(int signum)
{
	if (signum == SIGINT)
	{
		g_d.exit_status = 1;
		ft_putstr_fd("\033[1;31m", 1);
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	ft_get_pwd_for_prompt(t_data *f, char *pwd)
{
	char	*s;

	if (getcwd(pwd, PATH_MAX - 1) == NULL)
	{
		s = ft_find_env("PWD", f->my_env);
		if (s)
		{
			ft_strlcpy(pwd, s, (PATH_MAX > ft_strlen(s) + 1) * (ft_strlen(s)
					+ 1) + (PATH_MAX <= ft_strlen(s) + 1) * PATH_MAX);
		}
		else
			ft_strlcpy(pwd, "", 1);
	}
}

char	*put_prompt(t_data *f)
{
	char	*prompt;
	char	*s;
	char	*color;
	char	pwd[PATH_MAX];

	f->kill_here = 0;
	signal(SIGINT, signal_handler);
	tcsetattr(0, TCSANOW, &f->new_tty);
	ft_get_pwd_for_prompt(f, pwd);
	color = "\033[1;32m";
	if (f->exit_status != 0)
		color = "\033[1;31m";
	ft_putstr_fd(color, 1);
	prompt = ft_strjoin(pwd, " ~$ \033[0m");
	s = readline(prompt);
	free(prompt);
	signal(SIGINT, SIG_IGN);
	return (s);
}

void	start_shell(t_data *d)
{
	char	*rl;

	while (1)
	{
		rl = put_prompt(d);
		if (!rl)
		{
			ft_putendl_fd("exit", 1);
			tcsetattr(0, TCSANOW, &d->old_tty);
			exit(d->exit_status);
		}
		if (*rl)
		{
			add_history(rl);
			if (pars(d, rl))
				continue ;
			if (!d->kill_here && d->list_of_cmd)
				exec_cmd(d);
			free_all(d);
		}
		else
			d->exit_status = 0;
		free(rl);
	}
}

int	main(int ac, char **av, char **env)
{
	signal(SIGQUIT, SIG_IGN);
	setup_shell(ac, av, env, &g_d);
	start_shell(&g_d);
	return (0);
}
