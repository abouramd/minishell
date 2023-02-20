/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouramd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 20:43:03 by abouramd          #+#    #+#             */
/*   Updated: 2022/10/11 10:55:40 by abouramd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	s1len;
	size_t	s2len;
	char	*p;

	if (!s1 || !s2)
		return (NULL);
	s1len = ft_strlen(s1);
	s2len = ft_strlen(s2);
	p = (char *)malloc((s1len + s2len + 1) * sizeof(char));
	if (!p)
		return (NULL);
	ft_strlcpy(p, s1, s1len + 1);
	ft_strlcat(p, s2, s1len + s2len + 1);
	return (p);
}
