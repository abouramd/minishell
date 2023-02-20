/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouramd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 16:39:10 by abouramd          #+#    #+#             */
/*   Updated: 2022/10/15 19:12:16 by abouramd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int a, size_t n)
{
	size_t			i;
	unsigned char	*str;
	unsigned char	c;

	str = (unsigned char *) s;
	c = (unsigned char) a;
	i = 0;
	while (i < n)
	{
		if (str[i] == c)
			return ((void *) s + i);
		i++;
	}
	return (NULL);
}
