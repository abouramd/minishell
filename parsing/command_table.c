/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_table.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zasabri <zasabri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 14:05:23 by zasabri           #+#    #+#             */
/*   Updated: 2023/02/18 09:06:27 by zasabri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

char	**fill_save(char **cmd, char **save)
{
	int		i;

	i = 0;
	while (cmd[i])
	{
		save[i] = ft_strdup(cmd[i]);
		i++;
	}
	save[i] = NULL;
	return (save);
}

char	**set_cmd(char **cmd, char *str)
{
	char	**save;
	int		i;

	i = 0;
	if (!cmd[0])
		cmd[0] = ft_strdup(str);
	if (cmd[i])
	{
		while (cmd[i])
			i++;
		save = (char **)malloc(sizeof(char *) * (i + 1));
		save = fill_save(cmd, save);
		cmd = (char **) malloc(sizeof(char *) * (i + 2));
		i = 0;
		while (save[i])
		{	
			cmd[i] = save[i];
			i++;
		}
		cmd[i] = ft_strdup(str);
		cmd [i + 1] = NULL;
	}
	//printf("%s\n", cmd[0]);
	return (cmd);
}
t_list	*command_table(t_list *lexer)
{
	t_list		*cmd_table;
	t_vals		*first;
	t_cmd_list	*save;

	save = NULL;
	cmd_table = NULL;
	save = initilize_save(save);
	first = (t_vals *) lexer->content;
	while (first->token != V_EOF)
	{
		if (first->token == V_STR)
			save->cmd = set_cmd(save->cmd, first->val);
		else if (first->token == V_LDIR)
		{
			for_lderiction(first, save, &lexer);
			printf("%d\n", save->infile);
		}
		else if (first->token == V_RDIR)
		{
			for_rderiction(first, save, &lexer);
			printf("%d\n", save->outfile);
		}
		else if (first->token == V_APP)
		{
			for_append(first, save, &lexer);
			printf("%d\n", save->outfile);
		}
		else if (first->token == V_PIPE)
		{
			ft_lstadd_back(&cmd_table, ft_lstnew(save));
			save = initilize_save(save);
		}
		lexer = lexer->next;
		first = (t_vals *) lexer->content;
	}
	ft_lstadd_back(&cmd_table, ft_lstnew(save));
	return (cmd_table);
}