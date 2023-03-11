/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouramd <abouramd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 18:22:54 by abouramd          #+#    #+#             */
/*   Updated: 2023/03/11 18:34:17 by abouramd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

char	*put_prompt(t_data *f)
{
	char	*prompt;
	char	*s;
	char	*color;
	char	pwd[PATH_MAX];

	f->kill_here = 0;
	signal(SIGINT, signal_handler);
	tcsetattr(0, TCSANOW, &f->new_tty);
	if (getcwd(pwd, PATH_MAX - 1) == NULL)
		ft_strlcpy(pwd, "minishell ~$", 13);
	color = "\033[1;32m";
	if (f->exit_status != 0)
		color = "\033[1;31m";
	ft_putstr_fd(color, 1);
	prompt = ft_strjoin(pwd, " >> \033[0m");
	s = readline(prompt);
	free(prompt);
	signal(SIGINT, SIG_IGN);
	return (s);
}

int	pars(t_data *d, char *rl)
{
	t_list		*lexer;
	t_here_doc	*hrd;

	lexer = NULL;
	hrd = NULL;
	lexer = lexecal_analyzer(rl);
	if (lexer == NULL || check_herdoc_limits(lexer) || syntax_error(lexer))
	{
		if (lexer)
		{
			d->exit_status = 258;
			free_lexer(lexer);
		}
		free(rl);
		return (1);
	}
	hrd = open_here_doc(d, lexer);
	d->list_of_cmd = NULL;
	if (!d->kill_here)
		d->list_of_cmd = command_table(d, hrd, lexer);
	else
		d->exit_status = 1;
	free_hrd(hrd);
	system("echo pars > leaks && leaks minishell | grep bytes >> leaks");/**/
	free_lexer(lexer);
	return (0);
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
			exit(0);
		}
		if (*rl)
		{
			add_history(rl);
			if (pars(d, rl))
				continue ;
			if (!d->kill_here && d->list_of_cmd)
				exec_cmd(d);
			free_all(d);
			system("echo exec >> leaks && leaks minishell | grep bytes >> leaks");/**/
		}
		else
			d->exit_status = 0;
		free(rl);
	}
}

int	main(int ac, char **av, char **env)
{
	setup_shell(ac, av, env, &g_d);
	start_shell(&g_d);
	return (0);
}
