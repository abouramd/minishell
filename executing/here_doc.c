/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouramd <abouramd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 08:24:05 by abouramd          #+#    #+#             */
/*   Updated: 2023/03/13 10:33:32 by abouramd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

char	*ft_get_lim(char *s, int *type)
{
	size_t	i;
	char	*lim;
	char	c;

	i = 0;
	c = 0;
	lim = NULL;
	*type = 1;
	if (s && (ft_strchr(s, '\"') || ft_strchr(s, '\'')))
		*type = 0;
	while (s && s[i])
	{
		if ((s[i] == '\"' || s[i] == '\'') && c == 0)
			c = s[i];
		else if (c && s[i] == c)
			c = 0;
		else
			lim = add_str(lim, s[i]);
		i++;
	}
	lim = add_str(lim, '\0');
	return (lim);
}

void	here_doc(int *fd_pipe, t_data *d, t_vals *first)
{
	char	*lim;
	char	*str;
	int		fd;
	int		type;

	lim = ft_get_lim(first->val, &type);
	fd = fd_pipe[1];
	close(fd_pipe[0]);
	while (1)
	{
		str = readline("\033[1;34mhere_doc\033[1;31m >> \033[0m");
		if (!str || !ft_strcmp(str, lim))
		{
			if (str)
				free(str);
			break ;
		}
		str = ft_expand_in_here_doc(d, str, type);
		ft_putendl_fd(str, fd);
		free(str);
	}
	free(lim);
	close(fd);
}

void	get_return_of_hrd(int *fd, int pid, t_data *d, t_here_doc *hrd)
{
	int	ret;

	waitpid(pid, &ret, 0);
	d->kill_here = WEXITSTATUS(ret);
	d->exit_status = WEXITSTATUS(ret);
	close (fd[1]);
	hrd->infile = fd[0];
}

void	for_herdoc(t_here_doc *hrd, t_data *d, t_vals *first, t_list **lexer)
{
	int		pid[2];
	int		fd[2];

	*lexer = (*lexer)->next;
	first = (t_vals *)(*lexer)->content;
	if (first->e_token == V_STR && !d->kill_here)
	{
		pid[0] = pipe(fd);
		if (pid[0] != -1)
			pid[1] = fork();
		if (pid[0] < 0 || pid[1] < 0)
		{
			ft_putendl_fd(strerror(errno), 2);
			d->exit_status = 1;
			d->kill_here = 1;
		}
		else if (pid[1] == 0)
		{
			signal(SIGINT, signal_here_doc);
			here_doc(fd, d, first);
			exit(0);
		}
		else
			get_return_of_hrd(fd, pid[1], d, hrd);
	}
}
