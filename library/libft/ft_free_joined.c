/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_joined.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouramd <abouramd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 04:05:30 by abouramd          #+#    #+#             */
/*   Updated: 2023/02/27 12:30:03 by abouramd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_free_joined(char *s1, char *s2, int d1, int d2)
{
	char	*p;

	if (!s1)
		s1 = ft_strdup("");
	if (!s1)
		return (NULL);
	if (!s2)
		s2 = ft_strdup("");
	if (!s2)
		return (NULL);
	p = ft_strjoin(s1, s2);
	if (p == NULL)
		return (NULL);
	if (d1)
		free(s1);
	if (d2)
		free(s2);
	return (p);
}
