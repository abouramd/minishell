/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zasabri <zasabri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 00:38:07 by zasabri           #+#    #+#             */
/*   Updated: 2023/02/27 16:08:10 by zasabri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

void	for_out_redirection(t_vals *first, t_cmd_list *save, t_list **lexer)
{
	*lexer = (*lexer)->next;
	first = (t_vals *) (*lexer)->content;
	if (first->token == V_STR)
	{
		if (save->outfile != 1)
			close(save->outfile);	
		save->outfile = open(first->val, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	}
}

void	for_input_redirection(t_vals *first, t_cmd_list *save, t_list **lexer)
{
	*lexer = (*lexer)->next;
	first = (t_vals *) (*lexer)->content;
	if (first->token == V_STR)
	{
		if (save->infile != 0)
			close(save->infile);
		save->infile = open(first->val, O_RDONLY, 0644);
	}
}
void	for_append(t_vals *first, t_cmd_list *save, t_list **lexer)
{
	*lexer = (*lexer)->next;
	first = (t_vals *) (*lexer)->content;
	if (first->token == V_STR)
	{
		if (save->outfile != 1)
			close(save->outfile);	
		save->outfile = open(first->val, O_CREAT | O_WRONLY | O_APPEND, 0644);
	}
}

void	for_herdoc(t_vals *first, t_cmd_list *save, t_list **lexer, int *exit_status)
{
	*lexer = (*lexer)->next;
	first = (t_vals *) (*lexer)->content;
	if (first->token == V_STR)
	{
		static int id;
    	static char *tty;
		char *tmp;
		if (!tty)
		{
			tty = ttyname(0);
			tmp = tty;
			tty = ft_strtrim(tty, "/dev");
			free(tmp);
		}
		char *name = ft_strjoin(ft_itoa(id), first->val);
		name = ft_strjoin(name, tty);
		char *lim = ft_strjoin(first->val, "\n");
		int pid;
		if (!*exit_status)
		{
			int ex = 0;
			pid = fork();
			if (pid == 0)
			{
				signal(SIGINT, SIG_DFL);
				char *str = get_next_line(0);
				char *line = "";
				while (str)
				{
					if (!ft_strncmp(str,lim, ft_strlen(str) + 1))
					{
						free(str);
						break;
					}
					line = ft_strjoin(line, str);
					free(str);
					str = get_next_line(0);
				}
				int fd = open(name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
				write(fd, line, ft_strlen(line));
				close(fd);
				exit (0);
			}
			waitpid(pid, &ex, 0);
			*exit_status = (ex != 0);
			if (save->infile != 0)
				close(save->infile);	
			save->infile = open(name, O_RDONLY, 0644);
			save->namehrd = name;
			id++;
		}
	}
}
