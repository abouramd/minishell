/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouramd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 13:50:34 by abouramd          #+#    #+#             */
/*   Updated: 2022/10/10 21:43:28 by abouramd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int a)
{
	size_t	index;
	char	c;
	char	*s;

	s = (char *) str;
	c = (char) a;
	index = 0;
	while (index <= ft_strlen(s))
	{
		if (s[index] == c)
			return (s + index);
		index++;
	}
	return (NULL);
}
