/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouramd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 11:51:13 by abouramd          #+#    #+#             */
/*   Updated: 2022/10/24 11:22:28 by abouramd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	a;
	size_t	lendest;
	size_t	lensrc;

	a = 0;
	lendest = 0;
	lensrc = 0;
	while (src[lensrc])
		lensrc++;
	if (dstsize == 0)
		return (lensrc);
	while (dst[lendest])
		lendest++;
	if (dstsize < lendest)
		return (lensrc + dstsize);
	while ((lendest + a + 1 < dstsize) && src[a])
	{
		dst[lendest + a] = src[a];
		a++;
	}
	dst[lendest + a] = '\0';
	return (lendest + lensrc);
}
