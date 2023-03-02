/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zasabri <zasabri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 07:59:21 by zasabri           #+#    #+#             */
/*   Updated: 2023/03/02 14:36:40 by zasabri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

char	*check_str(char *str, t_lex *check)
{
	char	*new_str;
    int     i;

    new_str = NULL;
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'')
		{
			check->v = 1;
			i++;
			new_str = add_str(new_str, '\0');
			while (str[i] && str[i] != '\'')
			{
				new_str = add_str(new_str, str[i]);
				i++;
			}
			if (str[i] == '\0')
				return (NULL);
			i++;
		}
		else if (str[i] == '\"')
		{
			i++;
			new_str = add_str(new_str, '\0');
			while (str[i] && str[i] != '\"')
			{
				new_str = add_str(new_str, str[i]);
				i++;
			}
			if (str[i] == '\0')
				return (NULL);
			i++;
		}
		else
		{
			new_str = add_str(new_str, str[i]);
			i++;
		}
	}
	return (new_str);
}