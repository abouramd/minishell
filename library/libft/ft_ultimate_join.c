/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ultimate_join.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouramd <abouramd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 06:06:22 by abouramd          #+#    #+#             */
/*   Updated: 2023/02/25 04:06:10 by abouramd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**checker(char **s1, char *s2)
{
	if (!s2)
		return (NULL);
	if (!s1)
	{
		s1 = (char **)malloc(sizeof(char *) * 1);
		if (!s1)
			return (NULL);
		s1[0] = NULL;
	}
	return (s1);
}

char	**ft_ultimate_join(char **s1, char *s2)
{
	size_t	size;
	char	**ret;

	size = 0;
	s1 = checker(s1, s2);
	if (!s1)
		return (NULL);
	while (s1[size])
		size++;
	ret = (char **)malloc(sizeof(char *) * (size + 2));
	if (!ret)
		return (NULL);
	size = 0;
	while (s1[size])
	{
		ret[size] = ft_strdup(s1[size]);
		size++;
	}
	ret[size++] = ft_strdup(s2);
	ret[size] = NULL;
	return (ret);
}
