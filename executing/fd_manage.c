/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_manage.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouramd <abouramd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 10:08:22 by abouramd          #+#    #+#             */
/*   Updated: 2023/03/05 13:26:56 by abouramd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	dup_fd(t_data *d)
{
	if (d->list_of_cmd->infile != 0)
	{
		if (d->list_of_cmd->infile < 0)
		{
			if (d->list_of_cmd->infile_errno == 300)
				ft_puterr(d->list_of_cmd->infile_name, "ambiguous redirect", 1);
			else
				ft_puterr(d->list_of_cmd->infile_name, strerror(d->list_of_cmd->infile_errno), 1);
		}
		else
		{
			dup2(d->list_of_cmd->infile, 0);
			close(d->list_of_cmd->infile);
		}
	}
	if (d->list_of_cmd->outfile != 1)
	{
		if (d->list_of_cmd->outfile < 0)
		{
			if (d->list_of_cmd->outfile_errno == 300)
				ft_puterr(d->list_of_cmd->outfile_name, "ambiguous redirect", 1);
			else
				ft_puterr(d->list_of_cmd->outfile_name, strerror(d->list_of_cmd->outfile_errno), 1);
		}
		else
		{
			dup2(d->list_of_cmd->outfile, 1);
			close(d->list_of_cmd->outfile);
		}
	}
}

void	give_fd(t_cmd_list *f, int infile, int outfile)
{
	if (f->infile == 0)
		f->infile = infile;
	else if (infile != 0)
		close(infile);
	if (f->outfile == 1)
		f->outfile = outfile;
	else if (outfile != 1)
		close(outfile);
}

void	close_useless_fd(t_cmd_list *cmd, int prev_fd)
{
	if (prev_fd != 0)
		close(prev_fd);
	while (cmd)
	{
		if (cmd->infile != 0)
		{
			close(cmd->infile);
			cmd->infile = 0;
		}
		if (cmd->outfile != 1)
		{
			close(cmd->outfile);
			cmd->outfile = 1;
		}
		cmd = cmd->next;
	}
}

void	close_fd_in_parent(t_data *d)
{
	if (d->list_of_cmd->infile != 0)
	{
		close(d->list_of_cmd->infile);
		d->list_of_cmd->infile = 0;
	}
	if (d->list_of_cmd->outfile != 1)
	{
		close(d->list_of_cmd->outfile);
		d->list_of_cmd->outfile = 1;
	}
}
