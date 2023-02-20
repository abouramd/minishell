/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouramd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 10:06:41 by abouramd          #+#    #+#             */
/*   Updated: 2022/10/19 12:10:42 by abouramd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *str, char (*f)(unsigned int, char))
{
	char	*p;
	size_t	index;

	index = 0;
	if (!str || !f)
		return (NULL);
	p = (char *)malloc(sizeof(char) * ft_strlen(str) + 1);
	if (!p)
		return (NULL);
	while (str[index])
	{
		p[index] = (*f)(index, str[index]);
		index++;
	}
	p[index] = '\0';
	return (p);
}
