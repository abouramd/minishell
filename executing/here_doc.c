/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouramd <abouramd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 08:24:05 by abouramd          #+#    #+#             */
/*   Updated: 2023/03/01 11:02:57 by abouramd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

char	*get_here_doc_name(t_data *d)
{
	static int	id;
	char		*tmp;
	char		*name;

	tmp = ft_itoa(id);
	name = ft_free_joined(tmp, d->tty, 1, 0);
	name = ft_free_joined("/tmp/.", name, 0, 1);
	id++;
	return (name);
}

void	here_doc(char *name, t_vals *first)
{
	char	*lim;
	char	*str;
	char	*line;
	int		fd;

	lim = ft_strjoin(first->val, "\n");
	line = NULL;
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
		line = ft_free_joined(line, str, 1, 1);
	}
	free(lim);
	fd = open(name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
		ft_puterr("FD here_doc", strerror(errno), 1);
	write(fd, line, ft_strlen(line));
	close(fd);
}

void	get_return_of_hrd(int pid, t_data *d, t_cmd_list *save, char *name)
{
	int	ret;

	waitpid(pid, &ret, 0);
	d->kill_here = WEXITSTATUS(ret);
	d->exit_status = WEXITSTATUS(ret);
	if (d->kill_here != 0)
		return ;
	if (save->infile > 0)
		close(save->infile);
	save->infile = open(name, O_RDONLY, 0644);
	if (save->infile == -1)
	{
		ft_puterr("FD here_doc", strerror(errno), 0);
		d->kill_here = 1;
		d->exit_status = 1;
	}
}

void	for_herdoc(t_data *d, t_vals *first, t_cmd_list *save, t_list **lexer)
{
	char	*name;
	int		pid;

	*lexer = (*lexer)->next;
	first = (t_vals *)(*lexer)->content;
	if (first->token == V_STR)
	{
		if (!d->kill_here)
		{
			name = get_here_doc_name(d);
			pid = fork();
			if (pid < 0)
				ft_putendl_fd(strerror(errno), 2);
			else if (pid == 0)
			{
				signal(SIGINT, signal_here_doc);
				here_doc(name, first);
				exit(0);
			}
			else
				get_return_of_hrd(pid, d, save, name);
			save->namehrd = name;
		}
	}
}
