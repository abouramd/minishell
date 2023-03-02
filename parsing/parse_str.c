/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zasabri <zasabri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 07:59:21 by zasabri           #+#    #+#             */
/*   Updated: 2023/03/01 16:40:39 by zasabri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

char	*check_str(char *str)
{
	char	*new_str;
    int     i;

    new_str = NULL;
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'')
		{	
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