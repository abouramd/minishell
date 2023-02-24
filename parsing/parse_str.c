/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouramd <abouramd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 07:59:21 by zasabri           #+#    #+#             */
/*   Updated: 2023/02/24 02:21:59 by abouramd         ###   ########.fr       */
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
	//printf("%s\n", new_str);
	return (new_str);
}