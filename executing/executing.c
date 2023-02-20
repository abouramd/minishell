/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouramd <abouramd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 06:51:59 by abouramd          #+#    #+#             */
/*   Updated: 2023/02/20 00:51:32 by abouramd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"
#include "exec.h"



void	signal_handler(int signal)
{
	if (signal == SIGINT)
	{
        write(1, "\n", 1);
	    rl_on_new_line();
	    rl_replace_line("", 0);
	    rl_redisplay();
    }
}

// void print_start(void)
// {
//     ft_putstr_fd("\033[1;32m\n", 1);
//     ft_putstr_fd("  \n", 1);
//     ft_putstr_fd("  ███╗   ███╗ ██╗ ███╗   ██╗ ██╗ ███████╗ ██╗  ██╗ ███████╗ ██╗      ██╗     \n", 1);
//     ft_putstr_fd("  ████╗ ████║ ██║ ████╗  ██║ ██║ ██╔════╝ ██║  ██║ ██╔════╝ ██║      ██║     \n", 1);
//     ft_putstr_fd("  ██╔████╔██║ ██║ ██╔██╗ ██║ ██║ ███████╗ ███████║ █████╗   ██║      ██║     \n", 1);
//     ft_putstr_fd("  ██║╚██╔╝██║ ██║ ██║╚██╗██║ ██║ ╚════██║ ██╔══██║ ██╔══╝   ██║      ██║     \n", 1);
//     ft_putstr_fd("  ██║ ╚═╝ ██║ ██║ ██║ ╚████║ ██║ ███████║ ██║  ██║ ███████╗ ███████╗ ███████╗\n", 1);
//     ft_putstr_fd("  ╚═╝     ╚═╝ ╚═╝ ╚═╝  ╚═══╝ ╚═╝ ╚══════╝ ╚═╝  ╚═╝ ╚══════╝ ╚══════╝ ╚══════╝\n", 1);
//     ft_putstr_fd("\033[0m\n", 1);
// }

char **alloc_env(char **s)
{
    char **ft_env;
    size_t  size = 0;
    
    if (s == NULL)
        return NULL;
    while (s[size])
        size++;
    ft_env = ft_calloc(size + 1, sizeof(char *));
    if (!ft_env)
        return NULL;
    size = 0;
    while (s[size])
    {
        ft_env[size] = ft_strdup(s[size]);
        size++;
    }
    ft_env[size] = NULL;
    return ft_env;
}

// char *put_prompt(t_data *f)
// {
//     char *prompt;
//     char *tmp;
//     char *s;
//     char pwd[1024];

//     signal(SIGINT, signal_handler);
//     getcwd(pwd, 1024);
//     tmp = ft_strjoin("\033[1;32m)", pwd);
//     prompt = ft_strjoin(tmp, " >> \033[0m");
//     s = readline(prompt);
//     free(prompt);
//     free(tmp);
//     signal(SIGINT, SIG_IGN);
//     return s;
// }


// int	main(int ac, char **av, char **env)
// {
//     char **cmd;
//     t_data d;
//     t_pipe f;
//     struct termios tty;
//     tcgetattr(0, &tty);
    
//     tty.c_lflag &= ~ECHOCTL;
//     tcsetattr(0, TCSANOW, &tty);
// 	(void)av;
// 	(void)ac;
// 	print_start();
// 	signal(SIGQUIT, SIG_IGN);
//     char **my_env = alloc_env(env);
// 	while (1)
// 	{
//         signal(SIGINT, signal_handler);
// 		rl = put_prompt();
//         signal(SIGINT, SIG_IGN);
// 		if (!rl)
// 		{
// 			write(1, "exit\n", 5);
// 			exit(0);
// 		}
// 		if (*rl)
//         {    
// 		    add_history(rl);
//             d.list_of_cmd->cmd = ft_split(rl, ' ');
//             f.path = split_path(env);
//             if (!cmd)
//                 exit(1);
//             if (!builtins(d.list_of_cmd->cmd, &my_env))
//                cmd_exec(&f, my_env, rl);
//         }
//         free(rl);
// 	}
// }

// void free_all(t_data *f)
// {
//     ft_free(f->list_of_cmd->cmd);
// }

// void setup_shell(int ac, char **av, char **env, t_data *d)
// {
//     t_term tty;
    
// 	(void)ac;
// 	(void)av;
//     tcgetattr(0, &tty);
//     tty.c_lflag &= ~ECHOCTL;
//     tcsetattr(0, TCSANOW, &tty);
//     signal(SIGQUIT, SIG_IGN);
// 	print_start();
//     d->exit_status = 0;
//     d->my_env = alloc_env(env);
// }

// int	main(int ac, char **av, char **env)
// {
//      char *rl;
//     t_data d;
//     t_cmd_list g;
//     t_pipe f;
    
//     setup_shell(ac, av, env, &d);
//     d.list_of_cmd = &g;
// 	while (1)
// 	{
// 		rl = put_prompt(&d);
// 		if (!rl)
// 			return (write(1, "exit\n", 5), 0);
// 		if (*rl)
//         {    
// 		    add_history(rl);
//             d.list_of_cmd->cmd = ft_split(rl, ' ');
//             d.list_of_cmd->infile = 0;
//             d.list_of_cmd->outfile = 1;
//             d.list_of_cmd->next = NULL;
//             f.path = split_path(d.my_env);
//             if (!d.list_of_cmd->cmd)
//                 exit(1);
//             if (!builtins(&d))
//                cmd_exec(&d, &f);
//             free_all(&d);
//             ft_free(f.path);
//         }
//         free(rl);
// 	}
// }