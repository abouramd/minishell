/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_characters.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zasabri <zasabri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 13:58:06 by zasabri           #+#    #+#             */
/*   Updated: 2023/02/15 13:58:10 by zasabri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

char	*add_str(char *str, char c)
{
	char	*charachter;
	char	*tmp;

	charachter = malloc(sizeof(char) * 2);
	charachter[0] = c;
	charachter[1] = '\0';
	if (!str)
	{
		str = charachter;
		return (str);
	}
	else
	{
		tmp = str;
		str = ft_strjoin(str, charachter);
		free(tmp);
		free(charachter);
	}
	return (str);
}
