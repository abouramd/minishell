/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouramd <abouramd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 08:24:05 by abouramd          #+#    #+#             */
/*   Updated: 2023/03/05 16:26:42 by abouramd         ###   ########.fr       */
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
	lim = add_str(lim, '\n');
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
		ft_putstr_fd("\033[1;34mhere_doc\033[1;31m >> \033[0m", 1);
		str = get_next_line(0);
		if (!str || !ft_strcmp(str, lim))
		{
			if (str)
				free(str);
			break ;
		}
		str = ft_expand_in_here_doc(d, str, type);
		write(fd, str, ft_strlen(str));
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
	int		pid;
	int		fd[2];

	*lexer = (*lexer)->next;
	first = (t_vals *)(*lexer)->content;
	if (first->token == V_STR && !d->kill_here)
	{
		pipe(fd);
		pid = fork();
		if (pid < 0)
		{
			ft_putendl_fd(strerror(errno), 2);
			d->exit_status = 1;
			d->kill_here = 1;
		}
		else if (pid == 0)
		{
			signal(SIGINT, signal_here_doc);
			here_doc(fd, d, first);
			exit(0);
		}
		else
			get_return_of_hrd(fd, pid, d, hrd);
	}
}
