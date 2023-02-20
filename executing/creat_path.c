/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouramd <abouramd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 16:23:01 by abouramd          #+#    #+#             */
/*   Updated: 2023/02/19 11:05:46 by abouramd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

char	*cpy_str(char *s)
{
	char	*p;
	int		i;

	i = 0;
	p = malloc(ft_strlen(s) + 1);
	if (!p)
		return (NULL);
	while (s[i])
	{
		p[i] = s[i];
		i++;
	}
	p[i] = '\0';
	return (p);
}

char	**split_path(char **env)
{
	int		i;
	char	**s;

	i = 0;
	s = NULL;
	while (env && env[i])
	{
		if (my_strstr(env[i], "PATH=") == 1)
		{
			s = ft_split(&env[i][5], ':');
			break ;
		}
		i++;
	}
	return (s);
}

char	*cmd_is_path(t_pipe *f)
{
	char	*s;

	s = NULL;
	if (access(f->cmd[0], F_OK | X_OK) == 0)
		s = cpy_str(f->cmd[0]);
	if (!s)
	{
		ft_puterr(f->cmd[0], strerror(2), 0);
	}
	return (s);
}

char	*link_cmd_path(t_pipe *f)
{
	int		i;
	char	*s;

	i = 0;
	s = NULL;
	while (f->path && f->path[i])
	{
		f->path[i] = myjoin(f->path[i], "/");
		f->path[i] = myjoin(f->path[i], f->cmd[0]);
		if (!f->path[i])
			exit(1);
		if (access(f->path[i], F_OK) == 0)
		{
			if (access(f->path[i], X_OK) == 0)
			{
				s = cpy_str(f->path[i]);
				break ;
			}
			else
				exit(126);
		}
		i++;
	}
	if (!s)
	{
		ft_puterr(f->cmd[0], "command not found", 0);
		ft_free(f->cmd);
	}
	ft_free(f->path);
	return (s);
}
 
char	*creat_path(t_data *d, t_pipe *f)
{
	char	*s;

	s = NULL;
	f->cmd = d->list_of_cmd->cmd;
	if (!d->list_of_cmd->cmd[0])
		ft_puterr(d->list_of_cmd->cmd[0], "command not found", 0);
	else if (my_strstr(d->list_of_cmd->cmd[0], "/"))
		s = cmd_is_path(f);
	else
		s = link_cmd_path(f);
	if (s == NULL)
		exit(127);
	return (s);
}
