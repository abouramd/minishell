/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouramd <abouramd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 03:38:21 by abouramd          #+#    #+#             */
/*   Updated: 2023/02/22 11:41:49 by abouramd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

// void	cmd_exec(t_data *d,t_pipe *f)
// {
//     int sexit;
//     int i = fork();
//     if (!i)
//     {
//     sigaction(SIGINT, &d->old_sigint, NULL);
//     sigaction(SIGQUIT, &d->old_sigquit, NULL);
//     tcsetattr(0, TCSANOW, &d->old_tty);
//     if (d->list_of_cmd->infile != 0)
//     {
//         if (d->list_of_cmd->infile < 0)
//             ft_puterr(d->list_of_cmd->cmd[0], ": open fail in infile", 1);
//         else
//             dup2(d->list_of_cmd->infile, 0);
//     }   
//     if (d->list_of_cmd->outfile != 1)
//     {
//         if (d->list_of_cmd->outfile < 0)
//             ft_puterr(d->list_of_cmd->cmd[0], ": open fail in outfile", 1);
//         else
//             dup2(d->list_of_cmd->outfile, 1);
//     }
// 	d->pathname = creat_path(d, f);
// 	if (execve(d->pathname, d->list_of_cmd->cmd, d->my_env) == -1)
// 		ft_puterr(d->list_of_cmd->cmd[0], strerror(errno), 1);
//     }
//     waitpid(i, &sexit, 0);
//     d->exit_status = WEXITSTATUS(sexit);
//     if (WIFSIGNALED(sexit))
//         d->exit_status = 128 + sexit;
// }


int builtins(t_data *f)
{
    if (f->list_of_cmd->cmd && f->list_of_cmd->cmd[0])
    {
        if (!ft_strncmp(f->list_of_cmd->cmd[0], "pwd", 4))
            return (built_pwd(f), 1);
        else if (!ft_strncmp(f->list_of_cmd->cmd[0], "cd", 3))
            return (built_cd(f), 1);
        else if (!ft_strncmp(f->list_of_cmd->cmd[0], "unset", 6))
            return (built_unset(f), 1);
        else if (!ft_strncmp(f->list_of_cmd->cmd[0], "export", 7))
            return(built_export(f), 1);
        else if (!ft_strncmp(f->list_of_cmd->cmd[0], "exit", 5))
            return(built_exit(f), 1);
        else if (!ft_strncmp(f->list_of_cmd->cmd[0], "echo", 5))
            return(built_echo(f), 1);
        else if (!ft_strncmp(f->list_of_cmd->cmd[0], "env", 4))
            return(built_env(f), 1);
    }
    return 0;
}