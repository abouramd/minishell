/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouramd <abouramd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 02:44:17 by abouramd          #+#    #+#             */
/*   Updated: 2023/02/25 04:06:22 by abouramd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	size_t	index_x;
	size_t	index_y;

	index_x = 0;
	if (!*needle)
		return ((char *)haystack);
	while (haystack && haystack[index_x])
	{
		index_y = 0;
		while (haystack[index_x + index_y] == needle[index_y])
			if (!needle[++index_y])
				return ((char *)haystack + index_x);
		index_x++;
	}
	return (NULL);
}
