/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouramd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 11:08:29 by abouramd          #+#    #+#             */
/*   Updated: 2022/10/19 11:56:07 by abouramd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_ntos(char *p, int n, int index)
{
	int	stock;

	stock = 0;
	if (n < 0)
	{
		p[stock++] = '-';
		n *= -1;
	}
	p[index] = '\0';
	while (stock < index--)
	{
		p[index] = n % 10 + '0';
		n /= 10;
	}
	return (p);
}

char	*ft_itoa(int n)
{
	int		index;
	char	*p;
	int		stock;

	index = 1;
	stock = n;
	if (stock < 0)
		index++;
	while (stock > 9 || stock < -9)
	{
		stock /= 10;
		index++;
	}
	p = (char *)malloc(sizeof(char) * index + 1);
	if (!p)
		return (NULL);
	stock = 0;
	if (n == -2147483648)
	{
		ft_strlcpy(p, "-2147483648", index + 1);
		return (p);
	}
	return (ft_ntos(p, n, index));
}
