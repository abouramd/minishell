/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouramd <abouramd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 16:23:01 by abouramd          #+#    #+#             */
/*   Updated: 2023/03/01 17:45:04 by abouramd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

char	*cmd_is_path(t_data *d)
{
	char	*s;

	s = NULL;
	if (access(d->list_of_cmd->cmd[0], F_OK | X_OK) == 0)
		s = ft_strdup(d->list_of_cmd->cmd[0]);
	else if (access(d->list_of_cmd->cmd[0], F_OK) == 0)
		ft_puterr(d->list_of_cmd->cmd[0], "Permission denied", 126);
	else if (!s)
		ft_puterr(d->list_of_cmd->cmd[0], strerror(2), 127);
	return (s);
}

void	join_path_with_cmd(t_data *d)
{
	int	i;

	i = 0;
	while (d->path && d->path[i])
	{
		d->path[i] = ft_free_joined(d->path[i], "/", 1, 0);
		if (!d->path[i])
			ft_puterr(d->list_of_cmd->cmd[0], "malloc !!", 1);
		d->path[i] = ft_free_joined(d->path[i], d->list_of_cmd->cmd[0], 1, 0);
		if (!d->path[i])
			ft_puterr(d->list_of_cmd->cmd[0], "malloc !!", 1);
		i++;
	}
}

char	*link_cmd_path(t_data *d, char *set)
{
	int		i;
	char	*s;

	s = NULL;
	join_path_with_cmd(d);
	i = 0;
	while (d->path && d->path[i])
	{
		if (access(d->path[i], F_OK | X_OK) == 0)
		{
			s = ft_strdup(d->path[i]);
			if (!s)
				ft_puterr("strdup", "malloc!!", 1);
			break ;
		}
		i++;
	}
	i = 0;
	while (!s && d->path && d->path[i])
		if (access(d->path[i++], F_OK) == 0)
			ft_puterr(d->list_of_cmd->cmd[0], "Permission denied", 126);
	if (!s)
		ft_puterr(d->list_of_cmd->cmd[0], set, 127);
	return (s);
}

char	*creat_path(t_data *d)
{
	char	*s;
	char	*set;
	int choose;

	s = NULL;
	choose = 0;
	d->path = split_path(d, &choose);
	set = "command not found";
	if (choose == 1)
		set = strerror(2);
	if (!**d->list_of_cmd->cmd)
		ft_puterr(d->list_of_cmd->cmd[0], "command not found", 127);
	else if (ft_strstr(d->list_of_cmd->cmd[0], "/"))
		s = cmd_is_path(d);
	else
		s = link_cmd_path(d, set);
	return (s);
}
