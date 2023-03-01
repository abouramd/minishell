/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zasabri <zasabri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 00:48:54 by abouramd          #+#    #+#             */
/*   Updated: 2023/02/28 20:15:08 by zasabri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"
#include "exec.h"

void print_start(void)
{
	ft_putstr_fd("\033[1;32m\n", 1);
	ft_putstr_fd("  \n", 1);
	ft_putstr_fd("  ███╗   ███╗ ██╗ ███╗   ██╗ ██╗ ███████╗ ██╗  ██╗ ███████╗ ██╗      ██╗     \n", 1);
	ft_putstr_fd("  ████╗ ████║ ██║ ████╗  ██║ ██║ ██╔════╝ ██║  ██║ ██╔════╝ ██║      ██║     \n", 1);
	ft_putstr_fd("  ██╔████╔██║ ██║ ██╔██╗ ██║ ██║ ███████╗ ███████║ █████╗   ██║      ██║     \n", 1);
	ft_putstr_fd("  ██║╚██╔╝██║ ██║ ██║╚██╗██║ ██║ ╚════██║ ██╔══██║ ██╔══╝   ██║      ██║     \n", 1);
	ft_putstr_fd("  ██║ ╚═╝ ██║ ██║ ██║ ╚████║ ██║ ███████║ ██║  ██║ ███████╗ ███████╗ ███████╗\n", 1);
	ft_putstr_fd("  ╚═╝     ╚═╝ ╚═╝ ╚═╝  ╚═══╝ ╚═╝ ╚══════╝ ╚═╝  ╚═╝ ╚══════╝ ╚══════╝ ╚══════╝\n", 1);
	ft_putstr_fd("\033[0m\n", 1);
}

char *put_prompt(t_data *f)
{
	char *prompt;
	char *tmp;
	char *s;
	char *color;
	char pwd[1024];

	color = "\033[1;32m)";
	if (f->exit_status != 0)
		color = "\033[1;31m)";
	signal(SIGINT, signal_handler);
	tcsetattr(0, TCSANOW, &f->new_tty);
	getcwd(pwd, 1024);
	tmp = ft_strjoin(color, pwd);
	prompt = ft_strjoin(tmp, " >> \033[0m");
	s = readline(prompt);
	free(prompt);
	free(tmp);
	signal(SIGINT, SIG_IGN);
	f->exit_status = 0;
	return s;
}
void free_cmd(t_cmd_list *list)
{
	if (list->cmd)
		ft_free(list->cmd);
	if (list->infile != 0)
		close(list->infile);
	if (list->outfile != 1)
		close(list->outfile);
	if (list->namehrd)
	{
		unlink(list->namehrd);
		free(list->namehrd);
	}
	free(list);
}

void free_all(t_data *f)
{
	t_cmd_list *p = f->list_of_cmd;
	t_cmd_list *tmp = f->list_of_cmd;

	while (tmp)
	{
		tmp = p;
		tmp = tmp -> next;
		free_cmd(p);
		p = tmp;
	} 
}

void setup_shell(int ac, char **av, char **env, t_data *d)
{    
	(void)ac;
	(void)av;
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
}

void free_lexer(t_list *list)
{
	t_vals *tmp;
	t_list *p;
	
	while (list)
	{
		tmp = list->content;
		if (!tmp)
		{
			free(tmp->val);
			free(tmp);
		}
		p = list;
		list = list->next; 
		free(p);
	}   
}

char	*replace_the_value(char	*cmd, char *str)
{
	if (str)
		cmd = str;
	return (cmd);
}
int	main(int ac, char **av, char **env)
{
	char *rl; 
	t_data d;
	t_list *lexer;
	t_cmd_list *save;

	setup_shell(ac, av, env, &d);
	while (1)
	{
		rl = put_prompt(&d);
		if (!rl)
			return (write(1, "exit\n", 5),tcsetattr(0, TCSANOW, &d.old_tty), 0);
		if (*rl)
		{    
			add_history(rl);
			lexer = lexecal_analyzer(rl);
			//test(lexer);  
			if (lexer == NULL || all_is_good(lexer))
			{
				if (lexer)
					free_lexer(lexer);
				free(rl);
				continue;
			}
			d.list_of_cmd = command_table(lexer, &d.exit_status);
			save = d.list_of_cmd;
			int i = 0;
			if (save->cmd)
			{
				while (save->cmd[i])
				{
					if ((ft_strnstr(save->cmd[i], "$", ft_strlen(save->cmd[i]))))
							save->cmd[i] = replace_the_value(save->cmd[i], print_env_content(save->cmd[i], d.my_env));
					i++;
				}
			}
			free_lexer(lexer);
			if (!d.exit_status && d.list_of_cmd)
				pipeline(&d);
			free_all(&d);    
		}
		free(rl);
	}
}