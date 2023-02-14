/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouramd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 17:59:16 by abouramd          #+#    #+#             */
/*   Updated: 2022/10/24 12:49:05 by abouramd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*p;
	size_t	index;
	size_t	n;

	n = 0;
	if (!s)
		return (NULL);
	if (start <= ft_strlen(s))
		n = ft_strlen(s) - start;
	else
		return (ft_strdup(""));
	if (len < n)
		n = len;
	index = 0;
	p = (char *)malloc((1 + n) * sizeof(char));
	if (!p)
		return (NULL);
	ft_strlcpy(p, s + start, n + 1);
	return (p);
}
