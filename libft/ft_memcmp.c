/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouramd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 17:51:05 by abouramd          #+#    #+#             */
/*   Updated: 2022/10/11 10:37:50 by abouramd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*d1;
	unsigned char	*d2;
	size_t			index;

	index = 0;
	d1 = (unsigned char *) s1;
	d2 = (unsigned char *) s2;
	while (index < n)
	{
		if (d1[index] != d2[index])
			return (d1[index] - d2[index]);
		index++;
	}
	return (0);
}
