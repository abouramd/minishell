/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouramd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 10:32:29 by abouramd          #+#    #+#             */
/*   Updated: 2022/10/24 11:50:10 by abouramd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	index_x;
	size_t	index_y;

	index_x = 0;
	if (!*needle)
		return ((char *) haystack);
	if (len == 0)
		return (NULL);
	while (haystack[index_x] && index_x < len)
	{
		index_y = 0;
		while (haystack[index_x + index_y] == needle[index_y]
			&& index_x + index_y < len)
			if (!needle[++index_y])
				return ((char *)haystack + index_x);
		index_x++;
	}
	return (NULL);
}
