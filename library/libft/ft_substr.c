/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 17:59:16 by abouramd          #+#    #+#             */
/*   Updated: 2023/03/09 12:22:03 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*p;
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
	p = (char *)malloc((1 + n) * sizeof(char));
	if (!p)
		return (NULL);
	ft_strlcpy(p, s + start, n + 1);
	return (p);
}
