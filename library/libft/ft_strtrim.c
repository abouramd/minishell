/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouramd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 12:04:29 by abouramd          #+#    #+#             */
/*   Updated: 2022/10/18 12:00:31 by abouramd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*start;
	size_t	end;
	size_t	m;

	m = 0;
	if (!s1 || !set)
		return (NULL);
	start = (char *) s1;
	end = ft_strlen(s1);
	while (0 < end - 1 && ft_strchr(set, start[end - 1]))
		end--;
	while (ft_strchr(set, start[m]) && m < ft_strlen(s1))
		m++;
	return (ft_substr(start, m, end - m));
}
