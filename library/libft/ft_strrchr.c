/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouramd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 15:26:51 by abouramd          #+#    #+#             */
/*   Updated: 2022/10/11 15:31:28 by abouramd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int a)
{
	size_t		last_i;
	size_t		index;
	char		c;
	char		*s;

	s = (char *) str;
	c = (char) a;
	last_i = ft_strlen(s) + 1;
	index = 0;
	while (index <= ft_strlen(s))
	{
		if (s[index] == c)
			last_i = index;
		index++;
	}
	if (last_i != ft_strlen(s) + 1)
		return (&s[last_i]);
	return (NULL);
}
