/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_documents.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouramd <abouramd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 02:15:07 by zasabri           #+#    #+#             */
/*   Updated: 2023/03/05 10:09:24 by abouramd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

char	*remove_spaces(char *lexer)
{
	char	*str;
	int		i;

	i = 0;
	while (lexer[i] && lexer[i] != ' ')
		i++;
	str = malloc(i + 1);
	if (!str)
		return (0);
	i = 0;
	while (lexer[i] && lexer[i] != ' ')
	{
		str[i] = lexer[i];
		i++;
	}
	str [i] = '\0';
	return (str);
}

void	here_documents(t_list *lexer)
{
	t_vals		*first;
	char		*str;
	char		*path;
	char		*arr;
	int			fd;
	t_list		*ptr;

	ptr = NULL;
	first = (t_vals *) lexer->content;
	while (first->token != V_EOF)
	{
		if (first->token == V_HDK)
		{
			lexer = lexer->next;
			first = (t_vals *) lexer->content;
			if (first->token == V_STR)
			{
				path = ft_strjoin("/tmp/", first->val);
				arr = remove_spaces(first->val);
				fd = open(path, O_CREAT | O_RDWR, 0777);
				while (1)
				{
					str = readline("heredoc> ");
					if (!str)
						break ;
					if (!ft_strncmp(str, arr, ft_strlen(str))
						&& ft_strlen(str) == ft_strlen(arr))
					{
						free(str);
						break;
					}
					write(fd, str, ft_strlen(str));
					write(fd, "\n", 1);
					free(str);
				}
				close(fd);
				free(arr);
			}
		}
		lexer = lexer->next;
		first = (t_vals *) lexer->content;
	}
}
