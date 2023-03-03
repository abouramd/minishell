/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouramd <abouramd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 02:46:00 by abouramd          #+#    #+#             */
/*   Updated: 2023/02/25 04:06:56 by abouramd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(const char *d1, const char *d2)
{
	unsigned char	*s1;
	unsigned char	*s2;
	size_t			index;

	s1 = (unsigned char *)d1;
	s2 = (unsigned char *)d2;
	index = 0;
	while (s1 && s2 && (s1[index] || s2[index]))
	{
		if (s1[index] != s2[index])
			return (s1[index] - s2[index]);
		index++;
	}
	return (0);
}
