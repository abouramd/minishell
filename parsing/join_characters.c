/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_characters.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zasabri <zasabri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 13:58:06 by zasabri           #+#    #+#             */
/*   Updated: 2023/02/18 09:20:04 by zasabri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

char	*add_str(char *str, char c)
{
	char	*charachter;
	char	*save;

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
		save = str;
		str = ft_strjoin(str, charachter);
		free(save);
		free(charachter);
	}
	return (str);
}
