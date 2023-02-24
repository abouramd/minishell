/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouramd <abouramd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 16:23:01 by abouramd          #+#    #+#             */
/*   Updated: 2023/02/24 10:55:37 by abouramd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

char	*cmd_is_path(t_data *d)
{
	char	*s;

	s = NULL;
	if (access(d->list_of_cmd->cmd[0], F_OK) == 0)
	{
		if (access(d->list_of_cmd->cmd[0], X_OK) == 0)
			s = ft_strdup(d->list_of_cmd->cmd[0]);
	}
	else if (access(d->list_of_cmd->cmd[0], F_OK) == 0)
	{
		ft_puterr(d->list_of_cmd->cmd[0], "Permission denied", 0);
		exit(126);
	}
	else if (!s)
		ft_puterr(d->list_of_cmd->cmd[0], strerror(2), 0);
	return (s);
}

char	*link_cmd_path(t_data *d)
{
	int		i;
	char	*s;

	i = 0;
	s = NULL;
	while (d->path && d->path[i])
	{
		d->path[i] = myjoin(d->path[i], "/");
		d->path[i] = myjoin(d->path[i], d->list_of_cmd->cmd[0]);
		if (!d->path[i])
			exit(1);
		if (access(d->path[i], F_OK) == 0)
		{
			if (access(d->path[i], X_OK) == 0)
			{
				s = ft_strdup(d->path[i]);
				break ;
			}
		}
		i++;
	}
	if (!s)
	{
		i = 0;
		while (d->path && d->path[i])
		{
			if (access(d->list_of_cmd->cmd[0], F_OK) == 0)
			{
				ft_puterr(d->list_of_cmd->cmd[0], "Permission denied", 0);
				exit(126);
			}
			i++;
		}
	}
	if (!s)
		ft_puterr(d->list_of_cmd->cmd[0], "command not found", 0);
	return (s);
}
 
char	*creat_path(t_data *d)
{
	char	*s;

	s = NULL;
	d->path = split_path(d);
	if (!d->list_of_cmd->cmd[0])
		ft_puterr(d->list_of_cmd->cmd[0], "command not found", 0);
	if (my_strstr(d->list_of_cmd->cmd[0], "/"))
		s = cmd_is_path(d);
	else
		s = link_cmd_path(d);
	if (s == NULL)
		exit(127);
	return (s);
}
