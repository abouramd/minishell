/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_documents.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouramd <abouramd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 02:15:07 by zasabri           #+#    #+#             */
/*   Updated: 2023/03/05 12:23:51 by abouramd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

// char	*remove_spaces(char *lexer)
// {
// 	char	*str;
// 	int		i;

// 	i = 0;
// 	while (lexer[i] && lexer[i] != ' ')
// 		i++;
// 	str = malloc(i + 1);
// 	if (!str)
// 		return (0);
// 	i = 0;
// 	while (lexer[i] && lexer[i] != ' ')
// 	{
// 		str[i] = lexer[i];
// 		i++;
// 	}
// 	str [i] = '\0';
// 	return (str);
// }

// void	here_documents(t_list *lexer)
// {
// 	t_vals		*first;
// 	char		*str;
// 	char		*path;
// 	char		*arr;
// 	int			fd;
// 	t_list		*ptr;

// 	ptr = NULL;
// 	first = (t_vals *) lexer->content;
// 	while (first->token != V_EOF)
// 	{
// 		if (first->token == V_HDK)
// 		{
// 			lexer = lexer->next;
// 			first = (t_vals *) lexer->content;
// 			if (first->token == V_STR)
// 			{
// 				path = ft_strjoin("/tmp/", first->val);
// 				arr = remove_spaces(first->val);
// 				fd = open(path, O_CREAT | O_RDWR, 0777);
// 				while (1)
// 				{
// 					str = readline("heredoc> ");
// 					if (!str)
// 						break ;
// 					if (!ft_strncmp(str, arr, ft_strlen(str))
// 						&& ft_strlen(str) == ft_strlen(arr))
// 					{
// 						free(str);
// 						break ;
// 					}
// 					write(fd, str, ft_strlen(str));
// 					write(fd, "\n", 1);
// 					free(str);
// 				}
// 				close(fd);
// 				free(arr);
// 			}
// 		}
// 		lexer = lexer->next;
// 		first = (t_vals *) lexer->content;
// 	}
// }
// t_cmd_list	*open_here_doc(t_data *d, t_list *lexer)
// {
// 	t_cmd_list	*cmd_table;
// 	t_vals		*first;
// 	t_cmd_list	*save;

// 	save = NULL;
// 	cmd_table = NULL;
// 	save = initilize_save();
// 	first = (t_vals *)lexer->content;
// 	while (first->token != V_EOF)
// 	{
// 		if (first->token == V_STR)
// 			save->cmd = add_new(d, save->cmd, first->val);
// 		else if (first->token == V_IN_RDIR)
// 			for_input_redirection(d, first, save, &lexer);
// 		else if (first->token == V_OUT_RDIR)
// 			for_out_redirection(d, first, save, &lexer);
// 		else if (first->token == V_APP)
// 			for_append(d, first, save, &lexer);
// 		else if (first->token == V_HDK)
// 			for_herdoc(d, first, save, &lexer);
// 		else if (first->token == V_PIPE)
// 		{
// 			link_back(&cmd_table, save);
// 			d->exit_status = 0;
// 			save = initilize_save();
// 		}
// 		lexer = lexer->next;
// 		first = (t_vals *)lexer->content;
// 	}
// 	d->exit_status = 0;
// 	link_back(&cmd_table, save);
// 	return (cmd_table);
// }

static void	link_here_doc(t_here_doc **lst, t_here_doc *new)
{
	t_here_doc	*p;

	if (lst)
	{
		if (!(*lst))
		{
			*lst = new;
		}
		else
		{
			p = *lst;
			while (p->next)
				p = p->next;
			p->next = new;
		}
	}
}

static t_here_doc	*first_val_here_doc(void)
{
	t_here_doc	*here_doc;

	here_doc = malloc(sizeof(t_here_doc));
	here_doc->infile = 0;
	here_doc->next = NULL;
	return (here_doc);
}

t_here_doc	*open_here_doc(t_data *d, t_list *lexer)
{
	t_here_doc	*here_doc;
	t_here_doc	*tmp;
	t_vals		*first;
	int			save_exit;

	here_doc = NULL;
	tmp = NULL;
	first = (t_vals *)lexer->content;
	save_exit = d->exit_status;
	while (first->token != V_EOF)
	{
		if (first->token == V_IN_RDIR || first->token == V_OUT_RDIR
			|| first->token == V_APP)
			first = (t_vals *)lexer->content;
		else if (first->token == V_HDK)
		{
			tmp = first_val_here_doc();
			for_herdoc(tmp, d, first, &lexer);
			link_here_doc(&here_doc, tmp);
			tmp = NULL;
		}
		else if (first->token == V_PIPE)
			d->exit_status = 0;
		lexer = lexer->next;
		first = (t_vals *)lexer->content;
	}
	link_here_doc(&here_doc, tmp);
	d->exit_status = save_exit;
	return (here_doc);
}
