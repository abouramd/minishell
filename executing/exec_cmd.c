/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouramd <abouramd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 10:06:36 by abouramd          #+#    #+#             */
/*   Updated: 2023/03/10 11:41:48 by abouramd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	run_cmd(t_data *d)
{
	sigaction(SIGINT, &d->old_sigint, NULL);
	sigaction(SIGQUIT, &d->old_sigquit, NULL);
	tcsetattr(0, TCSANOW, &d->old_tty);
	dup_fd(d->list_of_cmd->infile, d->list_of_cmd->infile_errno,
		d->list_of_cmd->infile_name, 0);
	dup_fd(d->list_of_cmd->outfile, d->list_of_cmd->outfile_errno,
		d->list_of_cmd->outfile_name, 1);
	if (d->list_of_cmd->cmd)
	{
		d->pathname = creat_path(d);
		if (execve(d->pathname, d->list_of_cmd->cmd, d->my_env) == -1)
			ft_puterr(d->list_of_cmd->cmd[0], strerror(errno), 1);
	}
	exit(0);
}

int	creat_child(t_data *d, int prev_fd)
{
	int	id;

	id = fork();
	if (id == -1)
		ft_putendl_fd(strerror(errno), 2);
	else if (id == 0)
	{
		close_useless_fd(d->list_of_cmd->next, prev_fd);
		d->in_muti_pip = 1;
		if (!builtins(d))
			run_cmd(d);
		else
			exit(d->exit_status);
	}
	else
		close_fd_in_parent(d);
	return (id);
}

int	loop_for_pipe(t_data *d)
{
	int	fd[2];
	int	infile;
	int	outfile;
	int	id;

	infile = 0;
	outfile = 1;
	while (d->list_of_cmd)
	{
		fd[0] = 0;
		fd[1] = 1;
		if (d->list_of_cmd->next)
			pipe(fd);
		outfile = fd[1];
		give_fd(d->list_of_cmd, infile, outfile);
		id = creat_child(d, fd[0]);
		d->list_of_cmd = d->list_of_cmd->next;
		infile = fd[0];
	}
	return (id);
}

void	pipeline(t_data *d)
{
	int			id;
	t_cmd_list	*tmp;

	if (d->list_of_cmd->next != NULL || !builtins(d))
	{
		tmp = d->list_of_cmd;
		id = loop_for_pipe(d);
		d->list_of_cmd = tmp;
		waitpid(id, &d->exit_status, 0);
		if (WIFSIGNALED(d->exit_status))
			d->exit_status = 128 + WTERMSIG(d->exit_status);
		else
			d->exit_status = WEXITSTATUS(d->exit_status);
		while (wait(NULL) != -1)
			;
	}
}
