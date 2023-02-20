/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouramd <abouramd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 20:51:00 by abouramd          #+#    #+#             */
/*   Updated: 2022/11/19 00:08:24 by abouramd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*d;
	unsigned char	*s;
	size_t			index;

	index = 0;
	if (dst == src)
		return (dst);
	d = (unsigned char *) dst;
	s = (unsigned char *) src;
	while (index < n)
	{
		d[index] = s[index];
		index++;
	}
	return (dst);
}
