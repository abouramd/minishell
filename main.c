//
/* ************************************************************************** */
//
/*                                                                            */
//
/*                                                        :::      ::::::::   */
//
/*   main.c                                             :+:      :+:    :+:   */
// /*                                                    +:+ +:+
// +:+     */
// /*   By: zasabri <zasabri@student.42.fr>            +#+  +:+
// +#+        */
// /*                                                +#+#+#+#+#+
// +#+           */
//
/*   Created: 2023/02/20 00:48:54 by abouramd          #+#    #+#             */
//
/*   Updated: 2023/03/02 13:48:33 by zasabri          ###   ########.fr       */
//
/*                                                                            */
//
/* ************************************************************************** */

// #include "include.h"
// #include "exec.h"

// void print_start(void)
// {
// 	ft_putstr_fd("\033[1;32m\n", 1);
// 	ft_putstr_fd("  \n", 1);
// 	ft_putstr_fd("  ███╗   ███╗ ██╗ ███╗   ██╗ ██╗ ███████╗ ██╗  ██╗ ███████╗ ██╗      ██╗     \n",
// 1);
// 	ft_putstr_fd("  ████╗ ████║ ██║ ████╗  ██║ ██║ ██╔════╝ ██║  ██║ ██╔════╝ ██║      ██║     \n",
// 1);
// 	ft_putstr_fd("  ██╔████╔██║ ██║ ██╔██╗ ██║ ██║ ███████╗ ███████║ █████╗   ██║      ██║     \n",
// 1);
// 	ft_putstr_fd("  ██║╚██╔╝██║ ██║ ██║╚██╗██║ ██║ ╚════██║ ██╔══██║ ██╔══╝   ██║      ██║     \n",
// 1);
// 	ft_putstr_fd("  ██║ ╚═╝ ██║ ██║ ██║ ╚████║ ██║ ███████║ ██║  ██║ ███████╗ ███████╗ ███████╗\n",
// 1);
// 	ft_putstr_fd("  ╚═╝     ╚═╝ ╚═╝ ╚═╝  ╚═══╝ ╚═╝ ╚══════╝ ╚═╝  ╚═╝ ╚══════╝ ╚══════╝ ╚══════╝\n",
// 1);
// 	ft_putstr_fd("\033[0m\n", 1);
// }

// char *put_prompt(t_data *f)
// {
// 	char *prompt;
// 	char *tmp;
// 	char *s;
// 	char *color;
// 	char pwd[1024];

// 	color = "\033[1;32m)";
// 	if (f->exit_status != 0)
// 		color = "\033[1;31m)";
// 	signal(SIGINT, signal_handler);
// 	tcsetattr(0, TCSANOW, &f->new_tty);
// 	getcwd(pwd, 1024);
// 	tmp = ft_strjoin(color, pwd);
// 	prompt = ft_strjoin(tmp, " >> \033[0m");
// 	s = readline(prompt);
// 	free(prompt);
// 	free(tmp);
// 	signal(SIGINT, SIG_IGN);
// 	f->exit_status = 0;
// 	return (s);
// }
// void free_cmd(t_cmd_list *list)
// {
// 	if (list->cmd)
// 		ft_free(list->cmd);
// 	if (list->infile != 0)
// 		close(list->infile);
// 	if (list->outfile != 1)
// 		close(list->outfile);
// 	if (list->namehrd)
// 	{
// 		unlink(list->namehrd);
// 		free(list->namehrd);
// 	}
// 	free(list);
// }

// void free_all(t_data *f)
// {
// 	t_cmd_list *p = f->list_of_cmd;
// 	t_cmd_list *tmp = f->list_of_cmd;

// 	while (tmp)
// 	{
// 		tmp = p;
// 		tmp = tmp -> next;
// 		free_cmd(p);
// 		p = tmp;
// 	}
// }

// void setup_shell(int ac, char **av, char **env, t_data *d)
// {
// 	(void)ac;
// 	(void)av;
// 	tcgetattr(0, &d->new_tty);
// 	tcgetattr(0, &d->old_tty);
// 	d->new_tty.c_lflag &= ~ECHOCTL;
// 	tcsetattr(0, TCSANOW, &d->new_tty);
// 	sigaction(SIGINT, NULL, &d->old_sigint);
// 	sigaction(SIGQUIT, NULL, &d->old_sigquit);
// 	signal(SIGQUIT, SIG_IGN);
// 	signal(SIGINT, signal_handler);
// 	print_start();
// 	d->exit_status = 0;
// 	d->my_env = alloc_env(env);
// }

// void free_lexer(t_list *list)
// {
// 	t_vals *tmp;
// 	t_list *p;

// 	while (list)
// 	{
// 		tmp = list->content;
// 		if (!tmp)
// 		{
// 			free(tmp->val);
// 			free(tmp);
// 		}
// 		p = list;
// 		list = list->next;
// 		free(p);
// 	}
// }

// // char	*replace_the_value(char	*cmd, char *str)
// // {
// // 	if (str)
// // 		cmd = str;
// // 	return (cmd);
// // }
// int	main(int ac, char **av, char **env)
// {
// 	char		*rl;
// 	t_data		d;
// 	t_list		*lexer;
// 	//t_cmd_list *save;

// 	setup_shell(ac, av, env, &d);
// 	while (1)
// 	{
// 		rl = put_prompt(&d);
// 		if (!rl)
// 			return (write(1, "exit\n", 5),tcsetattr(0, TCSANOW, &d.old_tty), 0);
// 		if (*rl)
// 		{
// 			add_history(rl);
// 			lexer = lexecal_analyzer(rl);
// 			//test(lexer);
// 			if (lexer == NULL || all_is_good(lexer, d.my_env))
// 			{
// 				if (lexer)
// 					free_lexer(lexer);
// 				free(rl);
// 				continue ;
// 			}
// 			d.list_of_cmd = command_table(lexer, &d.exit_status);
// 			//save = d.list_of_cmd;
// 			//int i = 0;
// 			// if (save->cmd)
// 			// {
// 			// 	char *ptr;

// 			// 	while (save->cmd[i])
// 			// 	{
// 			// 		if ((ft_strnstr(save->cmd[i], "$",
// ft_strlen(save->cmd[i]))))
// 			// 				save->cmd[i] = replace_the_value(save->cmd[i],
// print_env_content(save->cmd[i], d.my_env));
// 			// 		i++;
// 			// 	}
// 			// 	ptr = save->cmd[i];
// 			// 	free(ptr);
// 			// }
// 			free_lexer(lexer);
// 			if (!d.exit_status && d.list_of_cmd)
// 				pipeline(&d);
// 			free_all(&d);
// 		}
// 		free(rl);
// 	}
// }

#include "exec.h"
#include "include.h"

void	print_start(void)
{
	ft_putstr_fd("\033[1;32m\n", 1);
	ft_putstr_fd("  ███╗   ███╗ ██╗ ███╗   ██╗ \
██╗ ███████╗ ██╗  ██╗ ███████╗ ██╗      ██╗     \n",
					1);
	ft_putstr_fd("  ████╗ ████║ ██║ ████╗  ██║ \
██║ ██╔════╝ ██║  ██║ ██╔════╝ ██║      ██║     \n",
					1);
	ft_putstr_fd("  ██╔████╔██║ ██║ ██╔██╗ ██║ \
██║ ███████╗ ███████║ █████╗   ██║      ██║     \n",
					1);
	ft_putstr_fd("  ██║╚██╔╝██║ ██║ ██║╚██╗██║ \
██║ ╚════██║ ██╔══██║ ██╔══╝   ██║      ██║     \n",
					1);
	ft_putstr_fd("  ██║ ╚═╝ ██║ ██║ ██║ ╚████║ \
██║ ███████║ ██║  ██║ ███████╗ ███████╗ ███████╗\n",
					1);
	ft_putstr_fd("  ╚═╝     ╚═╝ ╚═╝ ╚═╝  ╚═══╝ \
╚═╝ ╚══════╝ ╚═╝  ╚═╝ ╚══════╝ ╚══════╝ ╚══════╝\n",
					1);
	ft_putstr_fd("\033[0m\n", 1);
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

void	free_cmd(t_cmd_list *list)
{
	if (list->cmd)
		ft_free(list->cmd);
	if (list->infile != 0)
		close(list->infile);
	if (list->outfile != 1)
		close(list->outfile);
	if (list->infile_name)
		free(list->infile_name);
	if (list->outfile_name)
		free(list->outfile_name);
	free(list);
}

void	free_all(t_data *f)
{
	t_cmd_list	*p;
	t_cmd_list	*tmp;

	p = f->list_of_cmd;
	tmp = f->list_of_cmd;
	while (tmp)
	{
		tmp = p;
		tmp = tmp->next;
		free_cmd(p);
		p = tmp;
	}
}

void	setup_shell(int ac, char **av, char **env, t_data *d)
{
	char	*tmp;
	char	pwd[PATH_MAX];

	(void)ac;
	d->tty = ttyname(0);
	tmp = d->tty;
	d->tty = ft_strtrim(d->tty, "/dev/ttys");
	free(tmp);
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
	d->my_env = alloc_env(env);
	getcwd(pwd, PATH_MAX - 1);
	tmp = ft_strtrim(av[0], "./");
	tmp = ft_free_joined("/", tmp, 0, 1);
	tmp = ft_free_joined(pwd, tmp, 0, 1);
	ft_env_add("SHELL", tmp, &d->my_env);
	free(tmp);
}

void	free_lexer(t_list *list)
{
	t_vals	*tmp;

	if (list)
	{
		if (list->next)
			free_lexer(list->next);
		tmp = (t_vals *)list->content;
		if (tmp)
		{
			if (tmp->val && tmp->token == V_STR)
			 	free(tmp->val);
			free(tmp);
		}
		free(list);
	}
}

void	cmd_info(t_cmd_list *cmd)
{
	int	i;

	i = 0;
	while (cmd)
	{
		i = 0;
		while (cmd->cmd && cmd->cmd[i])
			printf("cmd -> %s\n", cmd->cmd[i++]);
		printf("infile -> %d\n", cmd->infile);
		printf("outfile -> %d\n", cmd->outfile);
		cmd = cmd->next;
	}
}

void	free_hrd(t_here_doc *h)
{
	if (h)
	{
		if (h->next)
			free_hrd(h->next);
		if (h->infile != 0)
			close(h->infile);
		free(h);
	}
}

int	pars(t_data *d, char *rl)
{
	t_list		*lexer;
	t_here_doc	*hrd;

	lexer = NULL;
	hrd = NULL;
	lexer = lexecal_analyzer(rl);
	if (lexer == NULL || syntax_error(lexer))
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
	free_hrd(hrd);
	//cmd_info(d->list_of_cmd);
	//system("echo pars > leaks && leaks minishell | grep bytes >> leaks");
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
				pipeline(d);
			free_all(d);
			//system("echo exec >> leaks && leaks minishell | grep bytes >> leaks");
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
